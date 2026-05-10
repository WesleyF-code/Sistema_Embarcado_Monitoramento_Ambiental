# 🌎 Sistema de Monitoramento Ambiental e Meteorológico

Projeto desenvolvido utilizando o Arduino Nano para aquisição e monitoramento de dados ambientais em tempo real.

O sistema realiza a leitura de:
- Temperatura
- Umidade relativa do ar
- Pressão atmosférica
- Altitude aproximada
- Luminosidade ambiente

Os dados são exibidos em tempo real através do Monitor Serial da IDE Arduino.

---

# 🧰 Hardware Utilizado

## Microcontrolador
- Arduino Nano

## Sensores
- BME280  
  - Temperatura
  - Umidade
  - Pressão atmosférica
  - Altitude aproximada

- BH1750  
  - Luminosidade ambiente

- MQ-135 *(em integração)*  
  - Qualidade do ar

---

# 🔌 Arquitetura do Sistema

## Comunicação I2C
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
