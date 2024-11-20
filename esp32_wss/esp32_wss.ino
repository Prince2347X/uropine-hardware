#include <ArduinoJson.h>      // For JSON formatting
#include <ESPAsyncWebServer.h>// For WebSocket
#include <WiFi.h>

const char* ssid = "Uropine Device 1";
const char* password = "rsi_12345";  // Wi-Fi credentials

const int inputPin = 34;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

String createJSON(int pressureData) {
  // Create a JSON object
  StaticJsonDocument<200> doc;
  doc["pressure"] = pressureData;
  doc["timestamp"] = millis();

  // Serialize JSON to string
  String output;
  serializeJson(doc, output);
  return output;
}

const int WINDOW_SIZE = 5;  // Number of readings to average
int readings[WINDOW_SIZE];  // Array to store readings
int readIndex = 0;         // Index for the current reading
int total = 0;            // Running total

int readPressure() {
    // Subtract the oldest reading from the total
  total = total - readings[readIndex];
  
  // Read the sensor
  int sensorValue = analogRead(inputPin);
  
  // Add the new reading to the total
  readings[readIndex] = sensorValue;
  total = total + sensorValue;
  
  // Advance to the next position in the array
  readIndex = (readIndex + 1) % WINDOW_SIZE;
  
  // Calculate and return the average
  return total / WINDOW_SIZE;
//  int sensorValue = analogRead(inputPin);
//  int pressure = sensorValue * (100 / 4095.0);
//  return pressure;
}

// WebSocket event handler
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("Client connected");
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("Client disconnected");
  }
}

void setup() {
  pinMode(inputPin, INPUT);
  Serial.begin(9600);  // For USB connection
  WiFi.softAP(ssid, password);  // Start ESP32 as an Access Point
  Serial.println("ESP32 Wi-Fi Access Point started");

  // Attach WebSocket events
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);

  // Start server
  server.begin();
}

void loop() {
  int pressureData = readPressure();
  String jsonData = createJSON(pressureData);

  // Send JSON data to all connected WebSocket clients
  ws.textAll(jsonData);

  // Also print data via USB serial
  Serial.println(pressureData);

  // Handle WebSocket client connections
  ws.cleanupClients();

  delay(500);
}
