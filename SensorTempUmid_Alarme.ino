// Example de Alarme por temperatura e umidade
// Lab. de Garagem
#include "DHT.h"
#define DHTPIN 9     // O pino onde o DHT vai esta conectado
// Descomente linha com o sensor que vai utilizar
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22 - RHT03 - AM2302
//#define DHTTYPE DHT21   // DHT 21 - AM2301 
DHT dht(DHTPIN, DHTTYPE);
#define ALARME 3 // pino onde o Alto-falante esta conectado
float tmax=50,tmin=0,temp, umid;
void setup() 
{
  Serial.begin(9600); 
  Serial.println("Alarme por temperatura e umidade");
  Serial.print("Digite a temperatura maxima: "); 
  while(tmax == 50)
  {
    if (Serial.available() > 0) 
    {  
      tmax= Serial.parseFloat();
    }
  }  
  Serial.println (tmax);
  Serial.print("Digite a temperatura minima: ");
  while(tmin == 0)
  {
    if (Serial.available() > 0) 
    {  
      tmin= Serial.parseFloat();
    }
  } 
  Serial.println (tmin);
  dht.begin();
}
void loop() 
{
  delay(2000); // delay para garantir no minimo 2s entre cada uma das leituras
  umid = dht.readHumidity(); // leitura de umidade
  temp = dht.readTemperature(); // leitura da temperatura
  if (isnan(temp) || isnan(umid)) //Verifica se é um valor válido 
  {
    Serial.println("\nFalha ao ler o Sensor DHT\n");
    tone (ALARME,440,1000); 
  } 
  else 
  {
    if (temp > tmin && temp < tmax)
    {
      noTone(ALARME);
      leituraSerial();
    }
    else
    {
      tone (ALARME,440,1000); 
      Serial.println("PERIGO!!! TEMPERATURA FORA DO ESPERADO");
      Serial.print("Temperatura deve estar entre ");
      Serial.print(tmin);
      Serial.print(" e ");
      Serial.println(tmax);
      leituraSerial();
    }
  }
}
void leituraSerial()
{
      Serial.print("Umidade relativa: "); 
      Serial.print(umid);
      Serial.print(" %\t");
      Serial.print("Temperature: "); 
      Serial.print(temp);
      Serial.println(" *C\n");
}
 
