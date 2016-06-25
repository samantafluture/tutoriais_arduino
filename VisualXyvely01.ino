/*Este código uso o sensor de luminosidade para medir a luz ambiente e então acender o LED em um valor inverso ao captado. Ou seja, se está muito escuro, o LED ficará muito claro. */

//setup
const int analogInPin = A2;  // pino do sensor  
int readingDelay = 10;  // tempo entre captação de dado  
int readingsPerSample = 10;  // número de captação por amostra  
boolean singleRead = false;   
boolean enableLED = true; 
const int ledPin = 9;  // pino do LED  

//variáveis
int sensorValue = 0; 
int outputValue = 0;  
int ledValue = 0;  
int sval;  
int sensorAvg;  
int tenTot;   

void setup() {  
// iniciar comunicação  
 Serial.begin(19200);   
pinMode(analogInPin, INPUT);  //configurar pino do sensor como input
pinMode(ledPin, OUTPUT);
}  
void loop() {  
if(!singleRead){  
//amotra de 10 captações   
for (int i=0; i<readingsPerSample; i++){  
     sval = analogRead(analogInPin); 
     tenTot = tenTot + sval; 
delay(readingDelay); 
   }  
   sensorAvg = (tenTot / 10);  //dividir total  
   tenTot = 0; //reset  
   outputValue = sensorAvg;  //definir média de captação  
 }else{   
   sensorValue = analogRead(analogInPin);  
   outputValue = sensorValue;  
 }  
//imprimir dados   
 Serial.print("Photocell= ");  
 Serial.println(outputValue); 
//acender led no nível da luz  
 ledValue = map(outputValue, 0, 1023, 255, 0); 
analogWrite(ledPin, ledValue);  //ligar led em valor específico
}


