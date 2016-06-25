/*
Este código cria um webserver com o wifi shield e mostra em uma página da internet os valores captados por até 6 sensores. Este código foi originalmente criado para o shield Wifi oficial, porém está adaptado para usar com o shield descrito acima também.
*/

#include <SPI.h>
#include <WiFi.h>


char ssid[] = "yourNetwork";      // nome da sua rede
char pass[] = "secretPassword";   // senha da sua rede
int keyIndex = 0;                 // key Index number da sua rede (apenas se a conexão for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  Serial.begin(9600); 

  
  // checar a presença do shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // não continuar
    while(true);
  } 
  
  // tentando conectar a rede wifi
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // conectar a rede WPA/WPA2. Mudar esta linha se está usando conexão WEP    
    status = WiFi.begin(ssid, pass);

    // esperar 10 segundos para conexão
    delay(10000);
  } 
  server.begin();
  // você está conectado, imprimir status
  printWifiStatus();
}


void loop() {
  // buscando por clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // pedido http termina com uma linha em branco
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // vc chegou ao final da linha
	// e a linha esta vazia
	// o pedido http terminou
	// então você pode responder
        if (c == '\n' && currentLineIsBlank) {
          // enviar resposta padrão no header http 
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output valor de cada input analógico dos sensores
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");       
          }
          client.println("</html>");
           break;
        }
        if (c == '\n') {
          // iniciando uma nova linha
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    
    // fechar conexão
    client.stop();
    Serial.println("client disonnected");
  }
}


void printWifiStatus() {
  // imprimir nome SSID da rede em que está conectado
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // imprimir IP da rede em que está conectado
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // imprimir força do sinal da conexão
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


