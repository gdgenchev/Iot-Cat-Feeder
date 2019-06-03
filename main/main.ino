#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include <FS.h>

const char* ssid = "Ne pipai!";
const char* password = "mnogoslojnaparola";

static const uint8_t D7 = 13;

ESP8266WebServer server(80);

Servo servo;


void setup() {
  Serial.begin(9600);
  
  SPIFFS.begin();
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  
  server.on("/", HTTP_GET, handleRoot);
  server.on("/feed", HTTP_GET, handleFeed);
  server.begin();
}

void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  server.streamFile(file, "text/html");
}

void handleFeed() {
  rotateServo();
  //check if above executed properly?
  File file = SPIFFS.open("/fedCat.html", "r");
  server.streamFile(file, "text/html");
}

void rotateServo() {
  servo.attach(D7);
  servo.write(0);
  delay(675);
  servo.write(100);
  delay(675);
  servo.detach();
}

void loop() {
  server.handleClient();
}
