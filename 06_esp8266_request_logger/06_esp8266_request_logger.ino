#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Laptop";
const char* password = "8918172922";

// Create an instance of the server
ESP8266WebServer server(80);

// (1). Middleware-like function to log request details
void logRequest(const String& method, const String& path) {
  IPAddress clientIP = server.client().remoteIP();  // Get the client's IP address
  Serial.println("Request from IP: " + clientIP.toString() + " Method: " + method + " Path: " + path);
}

// (2). Function to handle the root URL ("/") = (i.e, root-controller)
void handleRoot() {
  logRequest("GET", "/");
  server.send(200, "text/html", "<h1>ESP8266 Web Server</h1><p>Welcome to the ESP8266 server!</p>");
}

// (3). Function to handle the /status URL (status-controller)
void handleStatus() {
  logRequest("GET", "/status");
  String status = "ESP8266 Status\n";
  status += String("IP Address: ") + WiFi.localIP().toString() + "\n";
  status += String("WiFi Status: ") + (WiFi.status() == WL_CONNECTED ? "Connected" : "Not Connected") + "\n";
  server.send(200, "text/plain", status);
}

// (4). Function to handle the /ping URL (ping-controller)
void handlePing() {
  logRequest("GET", "/ping");
  server.send(200, "text/html", "<h1>Pong!</h1><p>Welcome to the ESP8266 server!</p>");
}

// (5). Function to handle wrong routes (wrong-route-controller)
void handleNotFound() {
  String method;

  // Determine the HTTP method of the request
  if (server.method() == HTTP_GET) {
    method = "GET";
  } else if (server.method() == HTTP_POST) {
    method = "POST";
  } else if (server.method() == HTTP_PUT) {
    method = "PUT";
  } else if (server.method() == HTTP_DELETE) {
    method = "DELETE";
  } else if (server.method() == HTTP_PATCH) {
    method = "PATCH";
  } else {
    method = "UNKNOWN";
  }

  // Log the method and route
  logRequest(method, server.uri());

  // Send a 404 response
  server.send(404, "text/html", "<h1>404 Not Found</h1><p>The page you requested does not exist.</p>");
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

  // (4). Handle all undefined routes (catch-all route)
  server.onNotFound(handleNotFound);

  // Start the server
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();
}
