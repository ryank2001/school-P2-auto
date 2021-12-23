#include <car.h>
#include <WiFi.h>

#define motorpin1 25
#define motorpin2 26
#define motorspeedpin 34 
#define servopin 27

const char* ssid = "VRV9517567E59";
const char* password = "3naNqtr9f7V4";
WiFiServer server(80);

unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// Auxiliar variables to store the current output state
String drivestate = "automatic";
String actionstate = "stopped";
String output27State = "off";

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;

String header;

void automaticDriving(){

}



void serverSetup(){
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
Car car(motorpin1,motorpin2, motorspeedpin, servopin);
void setup(){
  Serial.begin(115200);
  

  serverSetup();
}

void manualdriving(){
   WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            
              if (header.indexOf("GET /automatic") >= 0) {
              drivestate = "automatic";
              actionstate = "stopped";

            } else if (header.indexOf("GET /manual") >= 0) {
              drivestate = "manual";
            }
              if (header.indexOf("GET /stopped") >= 0) {
              actionstate = "stopped"; 
              }
              else if (header.indexOf("GET /forward") >= 0) {
              actionstate = "forward";
              }
              else if (header.indexOf("GET /backward") >= 0) {
              actionstate = "backward";
              }
              else if (header.indexOf("GET /left") >= 0) {
              actionstate = "left";
              }
              else if (header.indexOf("GET /right") >= 0) {
              actionstate = "right";
              }
            //need to add actions!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            
            
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>Car controlls</h1>");
            
            //bestuuring van de button die bepaald of de auto automatisch of manueel rijd.  
            client.println("<p>Current drive state: " + drivestate + "</p>");
            //is de drivestate manual is laat hij de bestuuringsknoppen zien, anders alleen de manual knop      
            if (drivestate=="automatic") {
              client.println("<p><a href=\"/manual\"><button class=\"button\">manual</button></a></p>");
            } else {
              client.println("<p><a href=\"/automatic\"><button class=\"button button2\">automatic</button></a></p>");
            
              client.println("<p>Current action: driving " + actionstate + "</p>");
              
              if (actionstate=="forward") {
                client.println("<p><a href=\"/stopped\"><button class=\"button\">stop</button></a></p>");

              } else {
                client.println("<p><a href=\"/forward\"><button class=\"button button2\">forward</button></a></p>");
                
              }

              if (actionstate=="backward") {
                client.println("<p><a href=\"/stopped\"><button class=\"button\">stop</button></a></p>");

              } else {
                client.println("<p><a href=\"/backward\"><button class=\"button button2\">backward</button></a></p>");
                
              }

              if (actionstate=="left") {
                client.println("<p><a href=\"/stopped\"><button class=\"button\">stop</button></a>");

              } else {
                client.println("<p><a href=\"/left\"><button class=\"button button2\">left</button></a>");
                
              }

              if (actionstate=="right") {
                client.println("<a href=\"/stopped\"><button class=\"button\">stop</button></a></p>");

              } else {
                client.println("<a href=\"/right\"><button class=\"button button2\">right</button></a></p>");
                
              }




              

            
            }
            client.println("</body></html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void loop(){
 manualdriving();
}
  
  
  