#include <Wire.h> 
#include <LiquidCrystal.h>

int pino_chuva = A0; //Analogico 0 para o pino do sensor de Chuva
int  chuva = 0; // Variável do pino analógica A0 do sinal vindo do sensor 

// Pinagem - display LCD
#define Luz_Fundo   7
LiquidCrystal lcd(8, 9, 5, 6, 3, 2);

void setup()   {
  Serial.begin(9600);  //Serial
  Serial.println("Lendo dados do sensor...");
  
  lcd.begin(16,2); //Inicializa LCD
  lcd.clear(); //Limpa o LCD
  pinMode(Luz_Fundo,OUTPUT); //define o pino como saída
  digitalWrite(Luz_Fundo,HIGH); // Liga a luz do display

}


void loop() {
  
  // Lê o valor do sensor e armazena em sensorValue
  chuva = analogRead(pino_chuva); 

       // Exibir informacoes no serial monitor
      Serial.print("Valor da chuva: ");
      Serial.println(chuva);
      
      // Exibir informacoes no display lcd
      lcd.setCursor(0,0);
      lcd.print("Chuva:");
      lcd.print(" ");
      lcd.setCursor(6,0);
      lcd.print(chuva);
           
        //Verifica qual é o valor e
        //imprime na Serial o valor e Status 
        if(chuva > 800){
          //Seco
          Serial.println("Seco");
          lcd.print(" Seco");
          
        }else if(chuva <=800 && chuva > 500 ){
          //Leve Chuva
          Serial.println("Chuva Fina");
          lcd.print(" Chuva Fina");//--
        
        }else if (chuva <= 500){
               //Chuva Forte
                Serial.println("Chuva Forte");
                lcd.print(" Chuva Forte");//--
        } 
        
        //aguarda 5 segundos para recomeçar
        delay(5000);

}
