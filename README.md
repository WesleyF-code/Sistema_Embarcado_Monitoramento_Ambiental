# 🌎 Sistema de Monitoramento Ambiental e Meteorológico

Projeto desenvolvido utilizando o Arduino Nano para aquisição e monitoramento de dados ambientais em tempo real.

O sistema realiza a leitura de:
- Temperatura
- Umidade relativa do ar
- Pressão atmosférica
- Altitude aproximada
- Luminosidade ambiente
- Qualidade relativa do ar *(em integração)*

Os dados são exibidos em tempo real através do Monitor Serial da IDE Arduino.

---

# 🧰 Hardware Utilizado

## Microcontrolador
- Arduino Nano

## Sensores

### BME280
Responsável por:
- Temperatura
- Umidade
- Pressão atmosférica
- Altitude aproximada

### BH1750
Responsável por:
- Luminosidade ambiente

### MQ-135 *(em integração)*
Responsável por:
- Monitoramento relativo da qualidade do ar

---

# 🏗️ Arquitetura do Sistema

O projeto utiliza uma arquitetura híbrida de aquisição de dados:

| Sensor | Tipo de Comunicação |
|---|---|
| BME280 | I2C |
| BH1750 | I2C |
| MQ-135 | Analógico (ADC) |

---

# 🔌 Barramento I2C

Os sensores BME280 e BH1750 compartilham o barramento I2C do Arduino Nano.

| Sinal | Arduino Nano |
|---|---|
| SDA | A4 |
| SCL | A5 |

---

# 🔧 Ligações dos Sensores

## BME280

| BME280 | Arduino Nano |
|---|---|
| VIN | 3V3 |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

Endereço I2C utilizado:

```cpp
0x76
```

---

## BH1750

| BH1750 | Arduino Nano |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SDA | A4 |
| SCL | A5 |
| ADDR | GND |

Endereço I2C padrão:

```cpp
0x23
```

---

## MQ-135 *(em desenvolvimento)*

| MQ-135 | Arduino Nano |
|---|---|
| VCC | 5V |
| GND | GND |
| AO | A0 |

---

# 📚 Bibliotecas Utilizadas

Instale as seguintes bibliotecas pela IDE Arduino:

- Adafruit BME280 Library
- Adafruit Unified Sensor
- BH1750

---

# 💻 Funcionalidades

✅ Leitura de temperatura  
✅ Leitura de umidade  
✅ Leitura de pressão atmosférica  
✅ Cálculo aproximado de altitude  
✅ Leitura de luminosidade  
✅ Comunicação I2C compartilhada  
✅ Exibição em tempo real no Monitor Serial  
🚧 Integração do MQ-135 em andamento  
🚧 Classificação relativa da qualidade do ar  

---

# 📟 Exemplo de Saída Serial

```text
========== DADOS AMBIENTAIS ==========

Temperatura: 27.4 C
Umidade: 63.2 %
Pressao: 1008.4 hPa
Altitude Aproximada: 42.7 m
Luminosidade: 315.0 lux

======================================
```

---

# 🧠 Conceitos Aplicados

- Sistemas embarcados
- Arquitetura de computadores
- Comunicação I2C
- Conversão analógico-digital (ADC)
- Aquisição de dados
- Sensoriamento ambiental
- Integração hardware/software
- Monitoramento meteorológico
- Sensoriamento digital

---

# ⚙️ Estrutura do Firmware

O firmware foi desenvolvido utilizando:
- Programação modular
- Bibliotecas específicas para sensores
- Comunicação serial para supervisão
- Leitura periódica de dados ambientais

---

# 🚀 Objetivo do Projeto

Desenvolver uma estação embarcada de monitoramento ambiental capaz de realizar aquisição e exibição de dados meteorológicos e ambientais em tempo real utilizando sensores digitais e analógicos.

---

# 📌 Status do Projeto

🚧 Em desenvolvimento

Próximas etapas:
- Integração completa do MQ-135
- Implementação de índice relativo da qualidade do ar
- Melhorias na interface serial
- Organização modular do firmware
- Documentação completa do hardware

---

# 👨‍💻 Autor

Wesley Ferreira Costa
