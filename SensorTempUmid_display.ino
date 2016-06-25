#include "DHT.h"
#include <LiquidCrystal.h>
#define Luz_Fundo   7

#define DHTPIN 9     

// definir o tipo de sensor que está usando
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// PINAGEM DO SENSOR:
// SAÍDA 1 (ESQUERDA) DO SENSOR - CONECTAR NO PINO 5V
// SAÍDÁ 2 DO SENSOR (DATA) - CONECTAR COM PINO 9
// SAÍDA 4 DO SENSOR (DIREITA) - CONECTAR COM PINO GND
// CONECTAR RESISTOR DE 10k - DO PINO 9 (DATA) À SAÍDA 1 (ESQUERDA/5V) DO SENSOR

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

//Define os pinos que serão ligados ao LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Array simbolo grau
byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,};

void setup() {
  Serial.begin(9600);
  Serial.println("Testando sensor!");
  
  dht.begin();

  lcd.begin(16,2); //Inicializa LCD
  lcd.clear(); //Limpa o LCD
  lcd.createChar(0, grau); //Cria o caractere customizado com o simbolo do grau
  pinMode(Luz_Fundo,OUTPUT); //define o pino como saída
  digitalWrite(Luz_Fundo,HIGH); // Liga a luz do display.
  
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Falha ao ler o sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  lcd.setCursor(0,0);
  lcd.print("Temperatura: ");
  lcd.print(" ");
  lcd.setCursor(13,0);
  lcd.print(t);
  lcd.setCursor(15,0);
  
  //Mostra o simbolo do grau formado pelo array
  lcd.write((byte)0);
  
  lcd.setCursor(0,1);
  lcd.print("Umidade: ");
  lcd.print(" ");
  lcd.setCursor(15,1);
  lcd.print(h);
 // lcd.setCursor(12,1);

  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Index calor: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
