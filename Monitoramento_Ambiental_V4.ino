#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>
#include <math.h>

// =========================
// OBJETOS DOS SENSORES
// =========================

Adafruit_BME280 bme;
BH1750 lightMeter;

// =========================
// CONFIGURAÇÕES
// =========================

#define SEALEVELPRESSURE_HPA (1013.25)
#define MQ135_PIN A0

bool bmeStatus = false;

// Constantes do MQ-135
#define RL_MQ135 1.0     // Resistor de carga (1.0 kOhm)
#define CURVA_A  110.47  // Constante 'a' da curva
#define CURVA_B  -2.862  // Constante 'b' da curva

float Ro_MQ135 = 10.0;   // Variável para guardar o Ro calibrado

// =========================
// FUNÇÕES DE CLASSIFICAÇÃO (ORIGINAIS)
// =========================

// ---------- TEMPERATURA ----------
String classificarTemperatura(float temp) {
  if (temp <= 15) {
    return "FRIO";
  } else if (temp <= 28) {
    return "MODERADO";
  } else if (temp <= 35) {
    return "QUENTE";
  } else {
    return "MUITO QUENTE";
  }
}

// ---------- UMIDADE ----------
String classificarUmidade(float umidade) {
  if (umidade < 30) {
    return "SECA";
  } else if (umidade <= 60) {
    return "CONFORTAVEL";
  } else if (umidade <= 80) {
    return "UMIDA";
  } else {
    return "MUITO UMIDA";
  }
}

// ---------- PRESSÃO ----------
String classificarPressao(float pressao) {
  if (pressao < 1000) {
    return "BAIXA";
  } else if (pressao <= 1020) {
    return "NORMAL";
  } else {
    return "ALTA";
  }
}

// ---------- LUMINOSIDADE ----------
String classificarLuminosidade(float lux) {
  if (lux < 50) {
    return "ESCURO";
  } else if (lux <= 300) {
    return "MODERADO";
  } else if (lux <= 1000) {
    return "CLARO";
  } else {
    return "MUITO CLARO";
  }
}

// =========================
// FUNÇÕES DO MQ-135 (NOVAS)
// =========================

// ---------- QUALIDADE DO AR (ANVISA RE-09/2003) ----------
String classificarQualidadeAr(float ppm) {
  if (ppm <= 450) {
    return "EXCELENTE (Ar Externo/Puro)";
  } else if (ppm <= 1000) {
    return "ADEQUADA (Dentro da Norma)";
  } else if (ppm <= 1500) {
    return "RUIM (Acima do limite ANVISA - Ventile o local)";
  } else {
    return "CRITICA (Risco a Saude)";
  }
}

// ---------- CALIBRAÇÃO ----------
float calibrarMQ135() {
  Serial.print("Calibrando MQ-135 no ar limpo...");
  float ro_soma = 0;
  
  for (int i = 0; i < 50; i++) {
    float v_out = analogRead(MQ135_PIN) * (5.0 / 1023.0);
    if (v_out > 0) {
      float rs = ((5.0 - v_out) / v_out) * RL_MQ135;
      ro_soma += rs;
    }
    delay(100);
  }
  
  float ro_final = ro_soma / 50.0;
  Serial.println(" Concluido!");
  Serial.print("Resistencia Base (Ro) calculada: ");
  Serial.print(ro_final);
  Serial.println(" kOhm");
  Serial.println();
  
  return ro_final;
}

// ---------- CÁLCULO DE PPM ----------
float calcularPPM(int leituraADC) {
  float v_out = leituraADC * (5.0 / 1023.0);
  if (v_out <= 0) return 0; 

  float r_s = ((5.0 - v_out) / v_out) * RL_MQ135;
  float razao = r_s / Ro_MQ135;
  
  float ppm = CURVA_A * pow(razao, CURVA_B);
  return ppm;
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
  } else {
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

  // Autocalibração do Ro (Necessário ar limpo na hora de ligar)
  Ro_MQ135 = calibrarMQ135();
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
  } else {
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
  int leituraBruta = analogRead(MQ135_PIN);
  float ppm = calcularPPM(leituraBruta);

  Serial.print("Qualidade do Ar: ");
  Serial.print(ppm);
  Serial.print(" PPM");
  Serial.print("  [");
  Serial.print(classificarQualidadeAr(ppm));
  Serial.println("]");
  Serial.println();

  Serial.println("======================================");
  Serial.println();

  delay(2000);
}