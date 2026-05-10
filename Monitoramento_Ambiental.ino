#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>

// =========================
// OBJETOS DOS SENSORES
// =========================

Adafruit_BME280 bme;
BH1750 lightMeter;

// =========================
// CONFIGURAÇÕES
// =========================

#define SEALEVELPRESSURE_HPA (1013.25)

// Variável para verificar se o BME280 foi encontrado
bool bmeStatus = false;


// =========================
// SETUP
// =========================

void setup() {

  Serial.begin(9600);
  Wire.begin();

  Serial.println("==================================");
  Serial.println(" SISTEMA DE MONITORAMENTO AMBIENTAL ");
  Serial.println("==================================");

  // Inicializa BME280
  // Trocado para endereco 0x76

  bmeStatus = bme.begin(0x76);

  if (!bmeStatus) {

    Serial.println("Erro ao encontrar o BME280!");
    Serial.println("Verifique conexoes e endereco I2C.");
    Serial.println();

  }

  else {

    Serial.println("BME280 inicializado com sucesso!");

  }

  // Inicializa BH1750
  lightMeter.begin();

  Serial.println("BH1750 inicializado com sucesso!");
  Serial.println();

}


// =========================
// LOOP PRINCIPAL
// =========================

void loop() {

  Serial.println("========== DADOS AMBIENTAIS ==========");

  // =========================
  // BME280
  // =========================

  if (bmeStatus) {

    float temperatura = bme.readTemperature();
    float umidade = bme.readHumidity();
    float pressao = bme.readPressure() / 100.0F;
    float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" C");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");

    Serial.print("Pressao: ");
    Serial.print(pressao);
    Serial.println(" hPa");

    Serial.print("Altitude Aproximada: ");
    Serial.print(altitude);
    Serial.println(" m");

  }

  else {

    Serial.println("BME280 indisponivel.");

  }

  // =========================
  // BH1750
  // =========================

  float luminosidade = lightMeter.readLightLevel();

  Serial.print("Luminosidade: ");
  Serial.print(luminosidade);
  Serial.println(" lux");

  Serial.println("======================================");
  Serial.println();

  delay(2000);

}