/*
Este código faz uma leitura dos valores captados pelo sensor, ou seja, os níveis de gás tóxico no ambiente em questão.
*/

// Definicoes dos pinos ligados ao sensor 
int pin_d0 = 7; 
int pin_a0 = A2;
int nivel_sensor = 250;
void setup()
{
  // Define os pinos de leitura do sensor como entrada
  pinMode(pin_d0, INPUT);
  pinMode(pin_a0, INPUT);
  // Inicializa a serial
  Serial.begin(9600);
}
void loop()
{
  // Le os dados do pino digital D0 do sensor
  int valor_digital = digitalRead(pin_d0);
  // Le os dados do pino analogico A0 do sensor
  int valor_analogico = analogRead(pin_a0);
  // Mostra os dados no serial monitor
  Serial.print("Pino D0 : ");
  Serial.print(valor_digital);
  Serial.print(" Pino A0 : ");
  Serial.println(valor_analogico);
  delay(100);
}

