#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "Laptop";
const char* password = "8918172922";

// Create an instance of the web server
ESP8266WebServer server(80);

void setup() {
  // Start the serial communication
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

  // Define the route
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/plain", "Hello, World!");
  });

  // Start the server
  server.begin();
  Serial.println("Server started.");
}

void loop() {
  // Handle client requests
  server.handleClient();
}
