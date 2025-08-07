# ESP32 BLE Beacon

Este projeto implementa um **beacon BLE** usando um ESP32 utilizando de ciclos controlados para economia de energia

## Funcionamento

- O ESP32 transmite um pacote BLE contendo uma string identificadora, neste caso sendo o "sala-rdc-01", por 10 segundos
- Após os 10 segundos, entra em um deep sleep de mais 10 segundos
- Ao fim do sleep, acorda e reinicia automaticamente, repetindo o processo

# Estrutura do Beacon

O beacon anuncia os seguintes dados:

- Flags BLE (0x01): modo discoverable
- Complete Name (0x09): "sala-rdc-01"

Para modificar o conteúdo transmitido, modifique o vetor "adv_raw_data[]" com o conteúdo desejado, mantendo um limite de 31 bytes por cada pacote enviado

# Ciclo de Funcionamento

- BLE é inicializado usando o stack Bluedroid da Espressif
- Advertisings dos dados começa com `esp_ble_gap_start_advertising()`
- Uma tarefa `stop_adv_task` aguarda 10 segundos
- Advertising é parado com `esp_ble_gap_stop_advertising()`
- No evento `ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT`, o chip entra em deep sleep
- Após o sleep, o ESP32 acorda e começa o ciclo novamente

# Estrutura dos Arquivos

`beacon_airqy.c`: Código principal do projeto
`CMakeLists.txt`: Arquivo padrão de build para ESP-IDF

# Compilando e executando o código

- Configure o ambiente ESP-IDF

  - Siga <https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/> para configuração

- Clone o repositório e execute estes comandos:
  - idf.py set-target esp32
  - idf.py menuconfig
    - Dentro de menuconfig, entre em Component Config, Bluetooth, e aperte Enter em Bluetooth
    - Salve a configuração apertando S e então saia do menuconfig
  - idf.py build

## Descobrindo qual a porta de conexão à ser usada

### Linux

- Antes de conectar o ESP32, abra um terminal e digite este comando:

  - ls /dev/tty*

- Conecte o ESP32 e então execute o comando acima novamente
- Com a nova conexão (Para exemplo, usaremos /dev/ttyUSB0) digite este comando:
  - idf.py -p /dev/ttyUSB0 flash monitor

Assim, o código de beacon_airqy.c será compilado e então injetado no ESP32, com o comando `monitor` exibindo o debugging do chip
