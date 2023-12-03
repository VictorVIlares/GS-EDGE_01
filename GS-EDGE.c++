#include <LiquidCrystal.h>

//definição de pinos
const int pinoSensorTemperatura = A0;
const int pinoLED = 9;
const int pinoBuzzer = 8;

// Definir pinos do LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Definindo limites de temperatura
float temperaturaCelsius;
const float limiteSuperior = 25.0;

void setup() {
  //configuração dos pinos do sensor, LED, Buzzer e LCD
  pinMode(pinoSensorTemperatura, INPUT);
  pinMode(pinoLED, OUTPUT);
  pinMode(pinoBuzzer, OUTPUT);
  lcd.begin(16, 2);  // LCD com 16 colunas e 2 linhas
  Serial.begin(9600); // Ativar o monitoramento no monitor serial
}

void loop() {
  // converter as leituras do sennsor TMP36 para Graus Celsius
  int valorSensor = analogRead(pinoSensorTemperatura);
  float tensaoSensor = (valorSensor / 1023.0) * 5.0;
  temperaturaCelsius = (tensaoSensor - 0.5) * 100.0;

  // atualizar a mensagem no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperaturaCelsius);
  lcd.print(" C");

  // Imprimir a temperatura no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperaturaCelsius);
  Serial.println(" °C");

  // Verificar se a temperatura ultrapassou o limite
  if (temperaturaCelsius > limiteSuperior) {
    // Acender o LED se a temperatura for superior ao limite
    digitalWrite(pinoLED, HIGH);

    // Ativar o Buzzer
    digitalWrite(pinoBuzzer, HIGH);

    // Atualizar mensagem no LCD para alerta de beber água
    lcd.setCursor(0, 1);
    lcd.print("Beba agua!");

  } else {
    // Desligar o LED e o Buzzer se a temperatura estiver dentro do limite
    digitalWrite(pinoLED, LOW);
    digitalWrite(pinoBuzzer, LOW);

    // Atualizar mensagem no LCD para normal
    lcd.setCursor(0, 1);
    lcd.print("Normal");
  }

  delay(1000); // Aguardar 1 segundo antes de ler a temperatura novamente
}
