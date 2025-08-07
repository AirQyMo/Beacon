# Beacon
Repositório para o código usado no ESP32 que transmite o ID da sala por BLE

---

## Ajuste do código 

- Pulso
Para ajustar o tempo de pulso e sleep, modifique as variáveis definidas por **`PULSO`** e **`SEGUNDOS`**

- Área do Beacon
Para ajustar a área afetada pelo pulso, ajuste `txPower` dentro de `raw_adv_data`. Lembre-se que txPower utiliza de decibéis

- Conteúdo do pulso
Para ajustar o conteúdo do pulso, neste caso uma string, modifique `complete name` dentro de `raw_adv_data`, ajustando o tamanho do pacote de acordo com o tamanho da string à ser transmitida (tipo de pacotes tem 1 byte de tamanho, até 23 bytes de comprimento visto os 31 bytes de limite que um pulso BLE transmite)

## Compilação 

Para compilar o código, visite o [github](https://github.com/espressif/esp-idf) da espressif, baixe o sdk junto de suas dependências e siga as instruções dependendo do seu sistema.

Após instalar o SDK junto de suas dependências e seguir o passo-a-passo para criação de um projeto, lembre-se de executar o comando `idf.py set-target esp32` e se certificar que o módulo bluetooth está ativado utilizando `idf.py menuconfig`, entrando em `components`, `bluetooth` e, caso o módulo não esteja selecionado, apertar enter (deve ficar assim [*] Bluetooth), salvando a configuração apertando a tecla S no teclado, e então saindo do menuconfig apertando a tecla ESC ou Q.  

Em UNIX, para saber a porta USB que o ESP32 está, execute no terminal `/dev/tty*` antes de conectar o ESP32, então, após conectar, execute o comenado novamente. A nova pasta criada será onde o ESP32 está conectado. Lembre-se que o polling-rate deve estar configurado para 115200 caso esteja usando programas como putty para monitoramento. 

Após compilação do firmware usando `idf.py build`, execute, em um terminal, `idf.py flash /dev/tty[Porta onde o ESP32 está] monitor`, isso fara upload do firmware no ESP32 e então monitorará as saidas do mesmo para garantir bom funcionamento. 
