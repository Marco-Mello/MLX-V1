#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

char IP_DEVICE[] = "35.175.238.71";





//  destino += IP_DEVICE;
 
void setup() {
 
  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("oe", "xicoxcomx");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 
}
 
void loop() {
  
 
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;    //Declare object of class HTTPClient

   String destino = "http://";
   destino = destino + IP_DEVICE;
   destino = destino + "/temperatura";
   
   http.begin(destino);      //Specify request destination
   http.addHeader("Content-Type", "application/json");  //Specify content-type header

  StaticJsonDocument<200> doc;
    JsonArray analogValues = doc.createNestedArray("analog");

    int value = analogRead(0);


    //CONVERSAO PARA O APPPPPPPPPPPPPP <<<<<<<<<<<<<<<<<<<<<<<<<
    value = (300 * value) / 1024;
    //value = (180*value) /300;

    //value = 0 - value;
  //================================================================
    
    // Add the value at the end of the array
    analogValues.add(value);
  



  char SerializadoJson[200];
  serializeJson(doc, SerializadoJson);



 
   int httpCode = http.POST(SerializadoJson);   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(1000);  //Send a request every 30 seconds
 
}
