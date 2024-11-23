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

// (2). Function to handle the /status URL (status-controller)
void handleStatus() {
  String status = "ESP8266 Status\n";
  status += String("IP Address: ") + WiFi.localIP().toString() + "\n";
  status += String("WiFi Status: ") + (WiFi.status() == WL_CONNECTED ? "Connected" : "Not Connected") + "\n";
  server.send(200, "text/plain", status);
}

// (3). Function to handle the /ping URL (ping-controller)
void handlePing() {
    server.send(200, "text/html", "<h1>Pong!</h1><p>Welcome to the ESP8266 server!</p>");
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
  Serial.println("Server is running : ");

  // (1). Handle the root ("/") route
  server.on("/", HTTP_GET, handleRoot);

  // (2). Handle the /status route
  server.on("/status", HTTP_GET, handleStatus);

  // (3). Handle the /ping route
  server.on("/ping", HTTP_GET, handlePing);

  // Start the server
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();
}