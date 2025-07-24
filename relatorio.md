# RELATÓRIO SOBRE CONSUMO ENERGÉTICO DO ESP32 COMO BEACON BLE

## Lucas Manoel Martins de Souza  
## 24 de Julho de 2025

---

## ESP32

O chip ESP32 pode ser alimentado tanto com 5 V quanto com 3.3 V. Durante os testes, observou-se que o consumo energético a 3.3 V foi significativamente menor em comparação a 5 V, o que impacta diretamente:

- no **tamanho da placa solar OPV necessária** para alimentar o sistema,
- e na **capacitância mínima** necessária para manter o chip ativo durante os pulsos de BLE.

---

## Funcionamento do chip

Inicialmente, o funcionamento do sistema consistia em:

1. Emitir um pacote BLE com uma string identificadora da sala.
2. Manter a transmissão por um tempo determinado.
3. Entrar em **deep sleep** para recarregar o capacitor via energia solar.

Foram testados três cenários de pulso/sleep:

- Pulso de 1 s e sleep de 60 s
- Pulso de 10 s e sleep de 10 s
- Pulso de 60 s e sleep de 60 s

---

## RESULTADOS (CORRIGIDOS)

### PULSO DE 10s / SLEEP DE 10s

#### 5 Volts
- Energia por ciclo: **25 J**
- Capacitor: **3.5 F**
- Suprir: **2.5 W por 10 s**
- Placa fotovoltaica: **~830 cm² (0.083 m²)**

#### 3.3 Volts
- Energia por ciclo: **8.25 J**
- Capacitor: **4.6 F**
- Suprir: **0.825 W por 10 s**
- Placa fotovoltaica: **~275 cm² (0.028 m²)**

---

### PULSO DE 1s / SLEEP DE 60s

#### 5 Volts
- Energia por ciclo: **2.5 J**
- Capacitor: **0.35 F**
- Suprir: **0.042 W por 60 s**
- Placa fotovoltaica: **~14 cm² (0.0014 m²)**

#### 3.3 Volts
- Energia por ciclo: **0.825 J**
- Capacitor: **0.46 F**
- Suprir: **0.0138 W por 60 s**
- Placa fotovoltaica: **~4.6 cm² (0.00046 m²)**

---

### PULSO DE 60s / SLEEP DE 60s

#### 5 Volts
- Energia por ciclo: **150 J**
- Capacitor: **21.3 F**
- Suprir: **2.5 W por 60 s**
- Placa fotovoltaica: **~830 cm² (0.083 m²)**

#### 3.3 Volts
- Energia por ciclo: **49.5 J**
- Capacitor: **27.5 F**
- Suprir: **0.825 W por 60 s**
- Placa fotovoltaica: **~275 cm² (0.028 m²)**

---

## Considerações finais

Reduzir o tempo de pulso para **1 segundo** e aumentar o tempo de **sleep para 60 segundos** apresentou uma **redução drástica na energia exigida**, permitindo uso de:

- Capacitores de baixa capacitância (sub-1 F),
- Placas OPV pequenas (5 a 15 cm²),
- Alto potencial de funcionamento com luz ambiente.

Esse formato é o mais eficiente e sustentável para alimentar o ESP32 operando como beacon com OPV.


