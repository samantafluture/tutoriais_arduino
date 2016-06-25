/* Este código grava dados de 3 sensores diferentes em um mesmo SD card, o máximo que o Arduino consegue coletar por shield/cartão. */

#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  

  Serial.print("Inicializando sd card...");
 
  // checar se o cartão está presente
  if (!SD.begin(chipSelect)) {
    Serial.println("sd card falhando ou não presente");
    return;
  }
  Serial.println("sd card inicializado");
}

void loop() {
  String dataString = "";

  // leitura de dados de três sensores (máximo permitido)
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ",";
    }
  }

  // abra o arquivo
  // apenas 1 arquivo pode ser aberto por vez
  // por isso é preciso fechar um antes de abrir o próximo
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // se o arquivo está disponível, escrever:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // mostrar dados no serial monitor também
    Serial.println(dataString);
  }
  // se o arquivo não está aberto, gerar mensagem de erro
  else {
    Serial.println("erro ao abrir datalog.txt");
  }
}


