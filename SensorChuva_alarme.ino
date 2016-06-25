/* Exemplo do Sensor de Chuva
BUZZER NO PINO 2 E GND 
SENSOR DE CHUVA NO GROUND + PINO 3 (COM RESISTOR DE 10K) E VCC
*/
int bip = 2;
int sensordechuva = 3;
void setup()
{
pinMode(bip,OUTPUT);
pinMode(sensordechuva,INPUT);
}
void loop()
{
if(digitalRead(sensordechuva) == 0)
{
digitalWrite(bip,HIGH);
delay(500);
digitalWrite(bip,LOW);
}
else
{
digitalWrite(bip,LOW);
}
delay(500);
}
