#include "WiFi.h"

#include "ESPAsyncWebServer.h"


const char* ssid = "Daanoontje";
const char* password = "Smikkelbakje";
AsyncWebServer server(80);


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
   WiFi.mode(WIFI_AP);

  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/i", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "https://youtu.be/dQw4w9WgXcQ");
  });
  server.begin();
}

void loop(){

  
}
