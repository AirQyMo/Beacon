#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_bt_main.h"
#include "esp_sleep.h"

#define TAG "BEACON"
#define SEGUNDOS 60
#define PULSO 1 // em segundos 

//pacotes seguem este padrao:
//tamanho do pacote (conteudo + tipo), tipo de pacote, conteudo do pacote
static uint8_t raw_adv_data[] = {
  //flags padrao (general discovery)
  0x02, 0x01, 0x06,

  //uuid
  //https://www.uuidgenerator.net/
  //uuid DEVE ter 128 bits, uuids menores (16 bits) possuem numeros reservados
  //https://www.bluetooth.com/wp-content/uploads/Files/Specification/HTML/Assigned_Numbers/out/en/Assigned_Numbers.pdf
  0x11, 0x07, 
  0x98, 0x8f, 0x73, 0xde, 0xfc, 0x38, 0x73, 0xb2, 0xf6, 0x42, 0x59, 0xda, 0x60, 0x52, 0x21, 0x4a,

  //txpower (+9dbm)
  0x02, 0x0a, 0x09
};

static esp_ble_adv_params_t adv_params = {
	.adv_int_min = 0x20, //20ms
	.adv_int_max = 0x20, //20ms 
	.adv_type = ADV_TYPE_NONCONN_IND,
	.own_addr_type = BLE_ADDR_TYPE_PUBLIC,
	.channel_map = ADV_CHNL_ALL,
	.adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY
};

void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
        case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
            ESP_LOGI(TAG, "Advertising data configurado. Iniciando beacon...");
            esp_ble_gap_start_advertising(&adv_params);
            break;
        case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
            ESP_LOGI(TAG, "Advertising iniciado.");
            break;
        case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
            ESP_LOGI(TAG, "Advertising parado.");
            esp_deep_sleep(SEGUNDOS * 1000000);
            break;
        default:
              break;
    }
}

void beacon_task(void *param)
{
  esp_ble_gap_config_adv_data_raw(raw_adv_data, sizeof(raw_adv_data));

  //func do freertos para criar um temporizador de PULSO segundos
  vTaskDelay(pdMS_TO_TICKS(PULSO * 1000));
  esp_ble_gap_stop_advertising();
  vTaskDelete(NULL);
}

void app_main(void)
{
	ESP_LOGI(TAG,"Iniciando beacon\n");

	esp_err_t ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ESP_ERROR_CHECK(nvs_flash_init());
	}

	ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));
	esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
	ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));
	ESP_ERROR_CHECK(esp_bluedroid_init());
	ESP_ERROR_CHECK(esp_bluedroid_enable());
	ESP_ERROR_CHECK(esp_ble_gap_register_callback(gap_event_handler));

	xTaskCreate(beacon_task, "beacon task", 2048, NULL, 5, NULL);
}
