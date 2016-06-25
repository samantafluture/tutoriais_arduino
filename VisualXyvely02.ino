/* Este código usa o shield Wifi acoplado ao Arduino para conectá-lo ao servidor Xyvely. Os dados captados, então, irão aparecer na página de usuário criada. */

#include <SPI.h>
#include <WiFi.h>
#include <HttpClient.h>
#include <Xively.h>

char ssid[] = "SSID_HERE"; //  sua rede SSID (nome) 
char pass[] = "PASS_HERE";    // senha da sua rede (use isso para WPA ou a chave abaixo para WEP)
int keyIndex = 0;            // para conexão WEP apenas

int status = WL_IDLE_STATUS;

// inseria aqui a sua chave Xively 
char xivelyKey[] = "API_KEY_HERE";
//inseria aqui o seu feed ID Xyvely
#define xivelyFeed FEED_ID_HERE
//insira aqui o nome dos canais que criou no Xyvely
char sensorID[] = "LIGHT_SENSOR_CHANNEL";
char ledID[] = "LED_CHANNEL";

// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
#define sensorPin A2
//led connected pin
#define ledPin 9
// Define the strings for our datastream IDs

  XivelyDatastream(sensorID, strlen(sensorID), DATASTREAM_FLOAT),
  XivelyDatastream(ledID, strlen(ledID), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(xivelyFeed, datastreams, 2 /* number of datastreams */);
WiFiClient client;
XivelyClient xivelyclient(client);
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm \n");
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //pin setup
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT); 
  Serial.println("Starting single datastream upload to Xively...");
  Serial.println();
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, keyIndex, pass);
    // wait 10 seconds for connection:
    delay(10000);
  } 
  Serial.println("Connected to wifi");
  printWifiStatus();
}
void loop() {
  //adjust LED level. set from Xively
  int getReturn = xivelyclient.get(feed, xivelyKey);    //get data from xively
  if(getReturn > 0){
    Serial.println("LED Datastream");
    Serial.println(feed[1]);
  }else Serial.println("HTTP Error");  
  //write value to LED - change brightness
  int level = feed[1].getFloat();
  if(level < 0){
    level = 0;
  }else if(level > 255){
    level = 255;
  }
  //actually write the value
  digitalWrite(ledPin, level);
//read sensor values
  int sensorValue = analogRead(sensorPin);
  datastreams[0].setFloat(sensorValue);  
  //print the sensor valye
  Serial.print("Read sensor value ");
  Serial.println(datastreams[0].getFloat());
//send value to xively
  Serial.println("Uploading it to Xively");
  int ret = xivelyclient.put(feed, xivelyKey);
  //return message
  Serial.print("xivelyclient.put returned ");
  Serial.println(ret);
  Serial.println("");
  //delay between calls
  delay(15000);
}

