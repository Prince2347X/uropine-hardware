/**
 * @file esp32_wss.ino
 * @brief ESP32 WebSocket Server for Pressure Sensor Data
 *
 * This code is designed to run on an ESP32 microcontroller and sets up a WebSocket server
 * to transmit pressure sensor data to connected clients. The ESP32 operates as a Wi-Fi
 * Access Point, allowing clients to connect and receive real-time pressure data in JSON format.
 *
 * @note This code is being used with version 0.5 of our hardware. We have used a best fit
 * equation to plot the graph in the app. The equation is as follows:
 * cm of H₂O = 0.282 × (sensor value) − 482.69
 *
 * Libraries used:
 * - ArduinoJson: For JSON formatting
 * - ESPAsyncWebServer: For WebSocket server functionality
 * - WiFi: For Wi-Fi connectivity
 *
 * Hardware connections:
 * - Pressure sensor connected to analog input pin 34
 *
 * Functionality:
 * - Reads pressure data from the sensor
 * - Formats the data into a JSON object
 * - Sends the JSON data to all connected WebSocket clients
 * - Prints the pressure data to the USB serial monitor
 *
 * WebSocket events:
 * - Client connect and disconnect events are logged to the serial monitor
 *
 * Wi-Fi credentials:
 * - SSID: "Uropine Device 1"
 * - Password: "rsi_12345"
 *
 * @version 0.5
 * @date 2024-10-01
 */

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

int readPressure() {
  int sensorValue = analogRead(inputPin);
  return sensorValue;
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
