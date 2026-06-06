# 🌎 Sistema de Monitoramento Ambiental e Meteorológico

Projeto desenvolvido utilizando o Arduino Nano para aquisição, processamento e monitoramento de dados ambientais em tempo real.

O sistema realiza a leitura de:

* Temperatura
* Umidade relativa do ar
* Pressão atmosférica
* Altitude aproximada
* Luminosidade ambiente
* Qualidade do ar em PPM

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

* Monitoramento da qualidade do ar
* Estimativa relativa de concentração de gases em PPM

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

```math
ADC=\frac{V_{in}}{V_{ref}}\cdot1023
```

Onde:

* (V_{in}) = tensão analógica do MQ-135
* (V_{ref}) = tensão de referência do Arduino (5V)

---

# 📊 Resolução do ADC

O ADC possui 1024 níveis de quantização:

```math
2^{10}=1024
```

Cada nível representa aproximadamente:

```math
\frac{5V}{1024}\approx4.88mV
```

Assim:

* 0V → 0
* 2.5V → ~511
* 5V → 1023

---

# 🧠 Processamento do MQ-135

Na versão atual do firmware, o sistema deixou de utilizar apenas valores brutos do ADC e passou a realizar uma estimativa relativa da concentração de gases em PPM (Partes por Milhão).

O firmware executa:

```cpp
int leituraBruta = analogRead(MQ135_PIN);
float ppm = calcularPPM(leituraBruta);
```

O processo ocorre em etapas:

1. O ADC converte a tensão analógica em valor digital
2. O firmware calcula a resistência interna do sensor ((Rs))
3. O sistema utiliza a razão (Rs/Ro)
4. Uma curva matemática do MQ-135 é aplicada
5. O resultado é convertido em PPM

---

# ⚙️ Autocalibração do MQ-135

Durante a inicialização do sistema, o firmware executa uma etapa automática de calibração.

```cpp
Ro_MQ135 = calibrarMQ135();
```

Nessa etapa:

* O sensor realiza múltiplas leituras em ambiente limpo
* O firmware calcula uma resistência média de referência ((Ro))
* Esse valor passa a ser utilizado nos cálculos de concentração em PPM

A autocalibração melhora significativamente a estabilidade e coerência das leituras ambientais.

---

# 📈 Conversão para PPM

O cálculo da concentração relativa de gases é realizado utilizando:

```cpp
float ppm = CURVA_A * pow(razao, CURVA_B);
```

Onde:

* `CURVA_A` e `CURVA_B` são constantes experimentais do MQ-135
* `razao` representa (Rs/Ro)

Essa abordagem permite obter estimativas mais próximas de medições reais de qualidade do ar.

---

# 🧪 Classificação da Qualidade do Ar

O sistema utiliza classificação baseada em PPM inspirada na resolução ANVISA RE-09/2003.

| Faixa PPM     | Classificação               |
| ------------- | --------------------------- |
| 0 – 450       | EXCELENTE (Ar Externo/Puro) |
| 451 – 1000    | ADEQUADA (Dentro da Norma)  |
| 1001 – 1500   | RUIM (Ventilar o ambiente)  |
| Acima de 1500 | CRÍTICA (Risco à saúde)     |

---

# 🌡️ Classificações Ambientais

O firmware também classifica automaticamente as demais variáveis ambientais.

## Temperatura

| Faixa       | Classificação |
| ----------- | ------------- |
| ≤ 15°C      | FRIO          |
| 16°C – 28°C | MODERADO      |
| 29°C – 35°C | QUENTE        |
| > 35°C      | MUITO QUENTE  |

## Umidade

| Faixa     | Classificação |
| --------- | ------------- |
| < 30%     | SECA          |
| 30% – 60% | CONFORTÁVEL   |
| 61% – 80% | ÚMIDA         |
| > 80%     | MUITO ÚMIDA   |

## Pressão Atmosférica

| Faixa           | Classificação |
| --------------- | ------------- |
| < 1000 hPa      | BAIXA         |
| 1000 – 1020 hPa | NORMAL        |
| > 1020 hPa      | ALTA          |

## Luminosidade

| Faixa          | Classificação |
| -------------- | ------------- |
| < 50 lux       | ESCURO        |
| 50 – 300 lux   | MODERADO      |
| 301 – 1000 lux | CLARO         |
| > 1000 lux     | MUITO CLARO   |

---

# 🔄 Fluxo Completo do Sistema

```text
Sensores ambientais
↓
Aquisição dos sinais
↓
Comunicação I2C e ADC
↓
ATmega328P processa os dados
↓
Firmware executa cálculos e classificações
↓
Estimativa de PPM do MQ-135
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

✅ Leitura de temperatura

✅ Leitura de umidade

✅ Leitura de pressão atmosférica

✅ Cálculo aproximado de altitude

✅ Leitura de luminosidade

✅ Comunicação I2C compartilhada

✅ Conversão analógico-digital via ADC

✅ Autocalibração do MQ-135

✅ Estimativa de concentração de gases em PPM

✅ Classificação ambiental automática

✅ Monitoramento da qualidade do ar

✅ Exibição em tempo real no Monitor Serial

---

# 📟 Exemplo de Saída Serial

```text
====================================
 SISTEMA DE MONITORAMENTO AMBIENTAL
====================================

BME280 inicializado com sucesso!
BH1750 inicializado com sucesso!
MQ-135 inicializado com sucesso!

Calibrando MQ-135 no ar limpo...
Concluido!
Resistencia Base (Ro) calculada: 9.87 kOhm

========== DADOS AMBIENTAIS ==========

Temperatura: 30.67 C [QUENTE]
Umidade: 63.86 % [UMIDA]
Pressao: 1009.58 hPa [NORMAL]
Altitude Aproximada: 37.81 m

Luminosidade: 6.67 lux [ESCURO]

Qualidade do Ar: 412.35 PPM
[EXCELENTE (Ar Externo/Puro)]

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
* Processamento matemático embarcado
* Estimativa de concentração gasosa em PPM

---

# ⚙️ Estrutura do Firmware

O firmware foi desenvolvido utilizando:

* Programação modular
* Bibliotecas específicas para sensores
* Comunicação serial para supervisão
* Leitura periódica de dados ambientais
* Processamento digital de sinais analógicos
* Conversão matemática para estimativa em PPM
* Classificação automática das variáveis ambientais

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

# 🚀 Objetivo do Projeto

Desenvolver uma estação embarcada de monitoramento ambiental capaz de:

* Adquirir dados ambientais em tempo real
* Processar sinais digitais e analógicos
* Estimar concentração relativa de gases em PPM
* Demonstrar integração hardware/software
* Aplicar conceitos de arquitetura de computadores
* Implementar aquisição e tratamento de dados em sistemas embarcados

---

# 👨‍💻 Autor

Wesley Ferreira Costa
