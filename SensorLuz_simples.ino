/*
Este código faz com que o sensor leia valores analógicos, medindo a luz ambiente usando o pino A0. Também faz ajustes e calibra as leitures captadas. 
*/

int sensorLuz = 0; 
int minLuz;          //usado para calibrar as leituras
int maxLuz;          //usado para calibrar as leituras
int luzNivel;
int ajustadoLuzNivel;

void setup() {
 Serial.begin(9600);
 luzNivel=analogRead(sensorLuz);
 minLuz=luzNivel-20;
 maxLuz=luzNivel;
}

void loop(){
 //auto-ajuste limites máx e min em tempo real
 luzNivel=analogRead(sensorLuz);
 if(minLuz>luzNivel){
 minLuz=luzNivel;
 }
 if(maxLuz<luzNivel){
 maxLuz=luzNivel;
 }
 //Ajuste no nível para produzir resultados entre  0 e 100.
 ajustadoLuzNivel = map(luzNivel, minLuz, maxLuz, 0, 100); 
 Serial.println(ajustadoLuzNivel);
 delay(50);
}

