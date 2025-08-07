# RELATÓRIO SOBRE COMPONENTES DO BEACON

## Lucas Manoel Martins de Souza

## 07 de Agosto de 2025

---

## BATERIA

Com o ESP32 necessitando de uma carga de 3.3V para funcionamento pleno, algumas opções de baterias e pilhas surgem como possível solução, sendo elas:

- **Bateria Li-Po**
  A opção preferida para um modelo finalizado visto que a mesma pode ser acoplada junto de um regulador de tensão e módulo carregador, possibilitando que o beacon seja carregado via USB.

- **Pilha AA**
  Similar à bateria Li-Po, porém sem a capacidade de ser carregada via USB.

- **Múltiplas pilhas AAA**
  Para fins de demonstração, três pilhas AAA, junto de um conversor de tensão, podem ser utilizadas para suprir o ESP32 com carga o suficiente para operação entre 40 à 120 horas, dependendo de picos de consumo e condições das pilhas. Oferece baixa duração quando comparada à outras opções e fornce o risco de instabilidade.

---

## MÓDULO CARREGADOR

Um módulo carregador pode ser utilizado junto de uma bateria Li-Po para fornecer a possibilidade de carregamento via USB, eliminando a necessidade de troca de pilhas e possibilidade de instalação de pilhas instáveis.

---

## REGULADOR DE TENSÃO

Necessitado em todos os casos, um regulador de tensão reduz a carga fornecida pela bateria ou pilhas e os ajusta para 3.3V, carga que o ESP32 naturalmente aceita. Dependendo da bateria ou pilha escolhida, o modelo do módulo muda dado as possíveis tensão que podem ser supridas. Pilhas AAA fornecem 1.5V Naturalmente, então ustilizar 3 pilhas supriria 4.5V, tensão que seria regulada para 3.3V pelo regulador de tensão e então suprida ao ESP32.

---

## CAPACITORES

No caso deste circuito, um capacitor serve para tanto suprir uma corrente suficiente de energia para que o beacon se inicie após saida do modo sleep, tanto para filtrar ruídos causados por picos de energia gerados pelo ESP32.
Algumas opções interessantes seriam super capacitores LDO, ou "Low Dropout Output", que possuem baixas correntes em idle e suportam entre 150mAh e 250mAh, o segundo valor sendo exatamente o mesmo valor que um pico de energia que o ESP32 causa ao iniciar.

---

## LINKS PARA OS COMPONENTES

Abaixo, segue uma lista com alguns links para lojas que fornecem os componentes mencionados

- [**Bateria Li-Po**](https://www.mercadolivre.com.br/bateria-recarregavel-lipo-37v-1000mah-conector-jstphr3/up/MLBU1091645563)

- [**Módulo carregador**](https://curtocircuito.com.br/carregador-bateria-lithium-1a-com-protecao-tp4056.html)

- [**Capacitor LDO**](https://www.acheicomponentes.com.br/transistores/transistor-regulador-de-tensao-ht7333-sot-89-smd)

- [**Pilhas AA**](https://www.lojaduracell.com.br/depto/pilhas-alcalinas/pilhas-aa-pequena)
