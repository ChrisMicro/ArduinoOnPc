/*

   first experimental webserver for ArduinoOnPC

   modified from 
   https://github.com/espressif/arduino-esp32/blob/master/libraries/WebServer/examples/HelloServer/HelloServer.ino
   

   15.2.2019 ChrisMicro

*/


#include "WebServer.h"

// try http://127.0.0.1:8888/
// in your browser

WebServer server(8888);

const int led = 13;

void handleRoot() {
  digitalWrite(led, 1);

  String str="hello from PC";

  server.send(200, "text/plain", str);
  digitalWrite(led, 0);
}

void handleNotFound() 
{
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);

  Serial.println("");

  server.on("/", handleRoot);

/*
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
*/

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) 
{
  server.handleClient();
}
