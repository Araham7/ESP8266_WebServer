#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>  // Add ArduinoJson library for handling JSON

// Replace with your network credentials
const char* ssid = "Laptop";
const char* password = "8918172922";

// Create an instance of the server
ESP8266WebServer server(80);

// (1). Middleware-like function to log request_details("HTTP_method" and  "path"):
void logRequest(const String& method, const String& path) {
  Serial.println("Request: " + method + " " + path);
}

// (2). Function to handle the root URL ("/"):
void handleRoot() {
  logRequest("GET" , "/"); // logging "HTTP_method" and  "path".
  // Create a JSON document
  StaticJsonDocument<200> doc;

  // Add data to the JSON document
  doc["success"] = true;
  doc["message"] = "You are on the root (/) page!";

  // Serialize JSON to string
  String jsonRootResponse;
  serializeJson(doc, jsonRootResponse);

  // Send JSON response
  server.send(200, "application/json", jsonRootResponse);
//  server.send(200, "text/html", "<h1>ESP8266 Web Server</h1><p>Welcome to the ESP8266 server!</p>");
}

// (3). Function to handle a custom URL ("/json"):
void handleJSON() {
  logRequest("GET" , "/json"); // logging "HTTP_method" and  "path".
  // Create a JSON document
  StaticJsonDocument<200> doc;

  // Add data to the JSON document
  doc["status"] = "success";
  doc["message"] = "This is a JSON response from the ESP8266 server!";
  doc["temperature"] = 25.3;  // Example of a temperature value

  // Serialize JSON to string
  String jsonResponse;
  serializeJson(doc, jsonResponse);

  // Send JSON response
  server.send(200, "application/json", jsonResponse);
}

// (4). Function to handle wrong or undefined routes:
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
  Serial.begin(9600);  // Changed to baud rate 9600

  delay(200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  // Print the IP address of the ESP8266
  Serial.println(WiFi.localIP());
  Serial.println("Server is started : ");

  // Define the routes : 
  server.on("/", HTTP_GET, handleRoot); // (1). Handle "/" request.
  server.on("/json", HTTP_GET, handleJSON); // (2). Handle "/json" request.
  server.onNotFound(handleNotFound); // Handle wrong_routes.

  // Start the server
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();
}



