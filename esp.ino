// Include the ESP8266 Library. This library is automatically provided by the ESP8266 Board Manager and does not need to be installed manually.
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

String codeVersion = "Version 1.0 by Ridgil";

// WiFi Router Login - change these to your router settings
const char* SSID = "";
const char* password = "";

String uuid = "";
String basicAuthHeader = "";

float humidity = 8.1f;

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println();
  Serial.println("Version 1.0  Dec 2020 by Ridgil");

    // Connect to WiFi network
  Serial.println();
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.print(SSID);
  WiFi.begin(SSID, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected to WiFi");
  Serial.println("");
  Serial.print("IP Address : ");
  Serial.print(WiFi.localIP());
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://192.168.1.23:8080/humidity/reading");      //Specify request destination
   http.addHeader("accept", "application/json");  //Specify content-type header
   http.addHeader("Authorization", basicAuthHeader);  //Specify content-type header`
   http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
   int httpCode = http.POST("{\"espUUID\": \"" + uuid + "\", \"value\": " + humidity + " }");   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
    Serial.println("Error in WiFi connection");   
 }

 delay(10000);
}
