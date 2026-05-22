# 🌎 Sistema de Monitoramento Ambiental e Meteorológico

Projeto desenvolvido utilizando o Arduino Nano para aquisição, processamento e monitoramento de dados ambientais em tempo real.

O sistema realiza a leitura de:

* Temperatura
* Umidade relativa do ar
* Pressão atmosférica
* Altitude aproximada
* Luminosidade ambiente
* Qualidade relativa do ar

Os dados são exibidos em tempo real através do Monitor Serial da IDE Arduino.

---

# 🧰 Hardware Utilizado

## Microcontrolador

* Arduino Nano
* Microcontrolador ATmega328P

---

# 🔍 Sensores Utilizados

## BME280

Responsável por:

* Temperatura
* Umidade
* Pressão atmosférica
* Altitude aproximada

Comunicação:

* Digital via I2C

---

## BH1750

Responsável por:

* Luminosidade ambiente

Comunicação:

* Digital via I2C

---

## MQ-135

Responsável por:

* Monitoramento relativo da qualidade do ar

Capaz de detectar:

* NH3
* CO2
* Fumaça
* Álcool
* Benzeno
* NOx
* Outros gases voláteis

Comunicação:

* Sinal analógico

---

# 🏗️ Arquitetura do Sistema

O projeto utiliza uma arquitetura híbrida de aquisição de dados:

| Sensor | Tipo de Comunicação |
| ------ | ------------------- |
| BME280 | I2C (Digital)       |
| BH1750 | I2C (Digital)       |
| MQ-135 | Analógico via ADC   |

---

# 🔌 Barramento I2C

Os sensores BME280 e BH1750 compartilham o barramento I2C do Arduino Nano.

| Sinal | Arduino Nano |
| ----- | ------------ |
| SDA   | A4           |
| SCL   | A5           |

O protocolo I2C permite múltiplos dispositivos conectados utilizando apenas dois fios de comunicação.

---

# 🔧 Ligações dos Sensores

## BME280

| BME280 | Arduino Nano |
| ------ | ------------ |
| VIN    | 3V3          |
| GND    | GND          |
| SDA    | A4           |
| SCL    | A5           |

Endereço I2C utilizado:

```cpp
0x76
```

---

## BH1750

| BH1750 | Arduino Nano |
| ------ | ------------ |
| VCC    | 3V3          |
| GND    | GND          |
| SDA    | A4           |
| SCL    | A5           |
| ADDR   | GND          |

Endereço I2C padrão:

```cpp
0x23
```

---

## MQ-135

| MQ-135 | Arduino Nano |
| ------ | ------------ |
| VCC    | 5V           |
| GND    | GND          |
| AO     | A0           |

---

# ⚙️ Funcionamento do MQ-135

O sensor MQ-135 utiliza um material semicondutor baseado em dióxido de estanho (SnO₂).

Internamente, o sensor possui:

* Uma camada sensível de SnO₂
* Um aquecedor interno
* Um circuito resistivo variável

O aquecedor mantém o sensor em temperatura adequada para detecção de gases.

Quando gases presentes no ambiente entram em contato com o material sensível:

* A resistência elétrica interna do sensor varia
* Essa variação altera a tensão de saída analógica do módulo

Quanto maior a concentração de determinados gases:

* Maior será a alteração da tensão analógica enviada ao Arduino

---

# 🔬 Conversão Analógico → Digital (ADC)

O MQ-135 fornece um sinal analógico contínuo ao pino A0 do Arduino Nano.

O ATmega328P possui um conversor analógico-digital (ADC) interno de 10 bits.

Isso significa que:

* Tensões analógicas entre 0V e 5V são convertidas em valores digitais entre 0 e 1023

A conversão segue aproximadamente a relação:

ADC=\frac{V_{in}}{V_{ref}}\cdot1023

Onde:

* $V_{in}$ = tensão analógica do MQ-135
* $V_{ref}$ = tensão de referência do Arduino (5V)

---

# 📊 Resolução do ADC

O ADC possui 1024 níveis de quantização:

2^{10}=1024

Cada nível representa aproximadamente:

\frac{5V}{1024}\approx4.88mV

Assim:

* 0V → 0
* 2.5V → ~511
* 5V → 1023

---

# 🧠 Como o Código Interpreta o MQ-135

No firmware, o Arduino realiza:

```cpp
int qualidadeAr = analogRead(MQ135_PIN);
```

A função `analogRead()`:

1. Mede a tensão analógica no pino A0
2. Executa a conversão ADC
3. Retorna um valor digital entre 0 e 1023

Quanto maior o valor:

* Maior a tensão detectada
* Maior a concentração relativa de gases

---

# 🧪 Classificação da Qualidade do Ar

O sistema utiliza uma classificação relativa baseada na leitura digital do ADC.

```cpp
if (valor <= 250)
```

Atualmente, os valores são classificados em:

| Faixa ADC    | Classificação |
| ------------ | ------------- |
| 0 – 250      | BOA           |
| 251 – 450    | MODERADA      |
| 451 – 700    | RUIM          |
| Acima de 700 | CRÍTICA       |

Essa classificação é:

* Experimental
* Relativa
* Não calibrada em PPM

O sistema atualmente NÃO mede concentração absoluta de gases.

Ele realiza:

* Monitoramento relativo da qualidade do ar
* Detecção de aumento de poluentes
* Identificação de alterações ambientais

---

# 🔄 Fluxo Completo do Sistema

```text
Gases no ambiente
↓
Variação da resistência do MQ-135
↓
Alteração da tensão analógica
↓
ADC do ATmega328P converte tensão em valor digital
↓
analogRead() retorna valor de 0–1023
↓
Firmware interpreta os dados
↓
Sistema classifica a qualidade do ar
↓
Dados exibidos no Monitor Serial
```

---

# 📚 Bibliotecas Utilizadas

Instale as seguintes bibliotecas pela IDE Arduino:

* Adafruit BME280 Library
* Adafruit Unified Sensor
* BH1750

---

# 💻 Funcionalidades

*✅ Leitura de temperatura
*✅ Leitura de umidade
*✅ Leitura de pressão atmosférica
*✅ Cálculo aproximado de altitude
*✅ Leitura de luminosidade
*✅ Comunicação I2C compartilhada
*✅ Conversão analógico-digital via ADC
*✅ Monitoramento relativo da qualidade do ar
*✅ Exibição em tempo real no Monitor Serial

---

# 📟 Exemplo de Saída Serial

```text
========== DADOS AMBIENTAIS ==========

Temperatura: 27.4 C
Umidade: 63.2 %
Pressao: 1008.4 hPa
Altitude Aproximada: 42.7 m

Luminosidade: 315.0 lux

Qualidade do Ar: 412 [MODERADA]

======================================
```

---

# 🧠 Conceitos Aplicados

* Sistemas embarcados
* Arquitetura de computadores
* Comunicação I2C
* Conversão analógico-digital (ADC)
* Aquisição de dados
* Sensoriamento ambiental
* Integração hardware/software
* Monitoramento meteorológico
* Sensoriamento digital
* Processamento de sinais analógicos
* Conversão de sinais físicos em dados digitais

---

# ⚙️ Estrutura do Firmware

O firmware foi desenvolvido utilizando:

* Programação modular
* Bibliotecas específicas para sensores
* Comunicação serial para supervisão
* Leitura periódica de dados ambientais
* Processamento digital de sinais analógicos

---

# 🏛️ Relação com a Arquitetura de Von Neumann

O projeto possui forte relação com os princípios da arquitetura clássica de Von Neumann.

A arquitetura de Von Neumann define um sistema computacional composto por:

* Unidade de processamento
* Memória
* Entrada de dados
* Saída de dados
* Barramentos de comunicação

No projeto desenvolvido:

| Arquitetura de Von Neumann | Projeto                     |
| -------------------------- | --------------------------- |
| Entrada de dados           | Sensores ambientais         |
| Processamento              | ATmega328P                  |
| Memória                    | RAM e Flash do Arduino Nano |
| Barramentos                | I2C e ADC                   |
| Saída de dados             | Monitor Serial              |

---

# 🔬 Comparativo Arquitetural

## Arquitetura Clássica de Von Neumann

Fluxo tradicional:

```text
Entrada
↓
Processamento
↓
Memória
↓
Saída
```

---

## Arquitetura Aplicada no Projeto

```text
Sensores
↓
Aquisição de sinais
↓
Conversão ADC/I2C
↓
ATmega328P processa os dados
↓
Firmware interpreta informações
↓
Saída serial em tempo real
```

---

# 🧩 Similaridades com Von Neumann

O sistema segue os princípios fundamentais de Von Neumann:

✅ Dados e instruções processados pela mesma CPU
✅ Uso de memória compartilhada
✅ Entrada e saída controladas pelo processador
✅ Execução sequencial do firmware
✅ Processamento centralizado no ATmega328P

---

# 🚀 Objetivo do Projeto

Desenvolver uma estação embarcada de monitoramento ambiental capaz de:

* Adquirir dados ambientais em tempo real
* Processar sinais digitais e analógicos
* Demonstrar integração hardware/software
* Aplicar conceitos de arquitetura de computadores
* Implementar aquisição e tratamento de dados em sistemas embarcados

---

# 👨‍💻 Autor

Wesley Ferreira Costa
