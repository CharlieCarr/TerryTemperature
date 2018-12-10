// ThingSpeak - Version: Latest 
#include <ThingSpeak.h>
#include <SPI.h>
#include <WiFi.h>
//Done with Libraries
WiFiClient client;
char ssid[] = "cs"; //define the SSID of the WiFi network
char pass[] = "gkmrxuW6"; // WiFi network password
int status = WL_IDLE_STATUS; //status of the WiFi Connection
//End WiFi Setup
unsigned long ChannelID = 644335;
const char * APIKey = "6E89FAY6MSJNYYNE";
//End Thingspeak setup

int sensorPin = 0; //Temperature sensor read pin

void setup() {
  
  Serial.begin(9600); //Default serial begin
  Serial.println("Attempting Network Connection..."); Serial.println("Please Wait..."); //Connect to the internet
  status = WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
  

  if ( status != WL_CONNECTED) {
    Serial.println("WiFi Not Connected");
    while (true);
  }
  else {
    Serial.println("**Network is Connected**");

  }

}

void loop() {

  int roomTemp = analogRead(sensorPin);  //create an integer to calculate the temperature
  float voltage = roomTemp * 5.0; //work out the voltage
  voltage /= 1024.0;
  // print out the voltage
  float tempC = (voltage - 0.5) * 100 ;
  Serial.print(tempC); Serial.println("C is the current temp"); //print the temperature to the console
  Serial.print(voltage); Serial.println(" Current Voltage");
  ThingSpeak.writeFields(ChannelID, APIKey);
  ThingSpeak.setField(1, tempC);
  ThingSpeak.setField(2, voltage);
  delay(200);
  
  if (tempC >= 30) { //If the temperature is over this number, the fan will start
    analogWrite(9, 250);
  }
}