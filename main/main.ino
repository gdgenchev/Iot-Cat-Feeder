#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "Ne pipai!";
const char* password = "mnogoslojnaparola";

const int SERVO_PIN = D7;

ESP8266WebServer server(80);

Servo servo;


void setup() {
  Serial.begin(9600);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  server.on("/", HTTP_GET, handleRoot);
  server.on("/feed", HTTP_GET, handleFeed);
  server.begin();
}

void handleRoot() {
  server.send(200, "text/html", "<form action=\"/feed\" method=\"GET\"><input type=\"submit\" value=\"Feed Cat\"></form>");
}

void handleFeed() {
  server.send(200, "text/html", "<html><title>Happy Cat</title><body><h1>You just fed the freakin' cat!</h1></body></html>");
  rotateServo();
}

void rotateServo() {
  servo.attach(SERVO_PIN);
  servo.write(0);
  delay(575);
  servo.write(60);
  delay(575);
  servo.detach();
}

void loop() {
  server.handleClient();
}
