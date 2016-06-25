#include <Thermistor.h> 

//Define os sensores
Thermistor temp(1);

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  int temperature = temp.getTemp();

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println("*C");
  
  delay(1000);
  
}
