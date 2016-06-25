/*
Este código faz o LED acender e apagar com o sensor de som.
É preciso determinar threshold para tornar os valores sensíveis.
Conecte o LED no pino 13 e o sensor de som no pino A0.
*/

int led = 13;
int threshold = 500; //mudar aqui conforme achar melhor
int volume;
void setup() {                
  Serial.begin(9600); 
pinMode(led, OUTPUT);     
}
void loop() {
  volume = analogRead(A0); // lê o valor do pino A0
/*
    //Debug mode
    Serial.println(volume);
    delay(100);
  */
if(volume>=threshold){
digitalWrite(led, HIGH); //liga o led
  }  
else{
digitalWrite(led, LOW); // desliga o led
  }
}

