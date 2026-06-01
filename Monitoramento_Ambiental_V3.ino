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

// Pino analógico do MQ-135
#define MQ135_PIN A0

// Variável para verificar se o BME280 foi encontrado
bool bmeStatus = false;


// =========================
// FUNÇÕES DE CLASSIFICAÇÃO
// =========================

// ---------- TEMPERATURA ----------

String classificarTemperatura(float temp) {

  if (temp <= 15) {

    return "FRIO";

  }

  else if (temp <= 28) {

    return "MODERADO";

  }

  else if (temp <= 35) {

    return "QUENTE";

  }

  else {

    return "MUITO QUENTE";

  }

}


// ---------- UMIDADE ----------

String classificarUmidade(float umidade) {

  if (umidade < 30) {

    return "SECA";

  }

  else if (umidade <= 60) {

    return "CONFORTAVEL";

  }

  else if (umidade <= 80) {

    return "UMIDA";

  }

  else {

    return "MUITO UMIDA";

  }

}


// ---------- PRESSÃO ----------

String classificarPressao(float pressao) {

  if (pressao < 1000) {

    return "BAIXA";

  }

  else if (pressao <= 1020) {

    return "NORMAL";

  }

  else {

    return "ALTA";

  }

}


// ---------- LUMINOSIDADE ----------

String classificarLuminosidade(float lux) {

  if (lux < 50) {

    return "ESCURO";

  }

  else if (lux <= 300) {

    return "MODERADO";

  }

  else if (lux <= 1000) {

    return "CLARO";

  }

  else {

    return "MUITO CLARO";

  }

}


// ---------- QUALIDADE DO AR ----------

String classificarQualidadeAr(int valor) {

  if (valor <= 40) {

    return "BOA";

  }

  else if (valor <= 50) {

    return "MODERADA";

  }

  else if (valor <= 60) {

    return "RUIM";

  }

  else {

    return "CRITICA";

  }

}


// =========================
// SETUP
// =========================

void setup() {

  Serial.begin(9600);
  Wire.begin();

  Serial.println("====================================");
  Serial.println(" SISTEMA DE MONITORAMENTO AMBIENTAL ");
  Serial.println("====================================");

  // =========================
  // Inicialização BME280
  // =========================

  bmeStatus = bme.begin(0x76);

  if (!bmeStatus) {

    Serial.println("Erro ao encontrar o BME280!");
    Serial.println("Verifique conexoes e endereco I2C.");
    Serial.println();

  }

  else {

    Serial.println("BME280 inicializado com sucesso!");

  }

  // =========================
  // Inicialização BH1750
  // =========================

  lightMeter.begin();

  Serial.println("BH1750 inicializado com sucesso!");

  // =========================
  // Inicialização MQ-135
  // =========================

  pinMode(MQ135_PIN, INPUT);

  Serial.println("MQ-135 inicializado com sucesso!");

  Serial.println();

}


// =========================
// LOOP PRINCIPAL
// =========================

void loop() {

  Serial.println("========== DADOS AMBIENTAIS ==========");
  Serial.println();

  // =========================
  // BME280
  // =========================

  if (bmeStatus) {

    float temperatura = bme.readTemperature();
    float umidade = bme.readHumidity();
    float pressao = bme.readPressure() / 100.0F;
    float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

    // TEMPERATURA

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" C");

    Serial.print("  [");
    Serial.print(classificarTemperatura(temperatura));
    Serial.println("]");

    // UMIDADE

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.print(" %");

    Serial.print("  [");
    Serial.print(classificarUmidade(umidade));
    Serial.println("]");

    // PRESSÃO

    Serial.print("Pressao: ");
    Serial.print(pressao);
    Serial.print(" hPa");

    Serial.print("  [");
    Serial.print(classificarPressao(pressao));
    Serial.println("]");

    // ALTITUDE

    Serial.print("Altitude Aproximada: ");
    Serial.print(altitude);
    Serial.println(" m");

  }

  else {

    Serial.println("BME280 indisponivel.");

  }

  Serial.println();

  // =========================
  // BH1750
  // =========================

  float luminosidade = lightMeter.readLightLevel();

  Serial.print("Luminosidade: ");
  Serial.print(luminosidade);
  Serial.print(" lux");

  Serial.print("  [");
  Serial.print(classificarLuminosidade(luminosidade));
  Serial.println("]");

  Serial.println();

  // =========================
  // MQ-135
  // =========================

  int qualidadeAr = analogRead(MQ135_PIN);

  Serial.print("Qualidade do Ar: ");
  Serial.print(qualidadeAr);

  Serial.print("  [");

  Serial.print(classificarQualidadeAr(qualidadeAr));

  Serial.println("]");

  Serial.println();

  Serial.println("======================================");
  Serial.println();

  delay(2000);

}
