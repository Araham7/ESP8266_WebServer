#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Laptop";
const char* password = "8918172922";

// Create an instance of the server
ESP8266WebServer server(80);

// (1). Function to handle the root URL ("/") = (i.e, root-controller)
void handleRoot() {
  server.send(200, "text/html", "<h1>ESP8266 Web Server</h1><p>Welcome to the ESP8266 server!</p>");
}

void setup() {
  // Start the serial communication for debugging
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  // Print the IP address of the ESP8266
  Serial.println(WiFi.localIP());

  // Handalling HOME("/") route :---
  server.on("/", HTTP_GET, handleRoot);

  // Start the server
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();
}

