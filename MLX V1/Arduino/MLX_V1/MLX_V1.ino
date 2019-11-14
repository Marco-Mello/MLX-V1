#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

char IP_WEBSERVER[] = "54.198.221.114";
char ID_DEVICE[] = "M3LL0"; //M3LL0 ou X1C0X


int temperatura_anterior = 0;


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
   destino = destino + IP_WEBSERVER;
   destino = destino + "/" + ID_DEVICE;
   destino = destino + "/temperatura";
   
   http.begin(destino);      //Specify request destination
   http.addHeader("Content-Type", "application/json");  //Specify content-type header

  StaticJsonDocument<200> doc;
    JsonArray analogValues = doc.createNestedArray("analog");


    int value = 0;
    for(int i = 0 ; i < 10 ; i++) value = value + analogRead(0);

    value = value/10;


    //CONVERSAO PARA O APPPPPPPPPPPPPP <<<<<<<<<<<<<<<<<<<<<<<<<
    value = (300 * value) / 1024;
    //value = (180*value) /300;

    //value = 0 - value;
  //================================================================
    
    // Add the value at the end of the array
    analogValues.add(value);
  



  char SerializadoJson[200];
  serializeJson(doc, SerializadoJson);


 if(temperatura_anterior == value ) {}
 else {
  
    int httpCode = http.POST(SerializadoJson);   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
  temperatura_anterior = value;
  }
 
   
 
   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(10);  //Send a request every 30 seconds
 
}
