# Uropine Device Hardware

This project uses an ESP32 microcontroller to read pressure data from a sensor and transmit it via WebSocket. Below is an explanation of the libraries used and the necessary configurations.

## Pre-requisites

1. Arduino IDE
2. CP2102 Driver

## Setup

1. Add Additional Board Manager URLs (For ESP32 and ESP8266 i.e. Node MCU):
    ```
    https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
    ```
2. Install `ESP32`/`ESP8266` board from Boards Manager
3. Select `ESP32 Wroom DA Module`/`NodeMCU 1.0 (ESP-12E Module)` boards
4. Install the libraries mentioned below
5. Compile and Uplaod the sketch accordingly

## Libraries Used

1. **ArduinoJson**
    - **Purpose**: This library is used for creating and formatting JSON objects. JSON (JavaScript Object Notation) is a lightweight data interchange format that is easy for humans to read and write, and easy for machines to parse and generate.
    - **Usage**: In the code, `ArduinoJson` is used to create a JSON object containing the pressure data and a timestamp, which is then serialized into a string for transmission.

2. **ESPAsyncWebServer**
    - **Purpose**: This library provides an asynchronous web server for the ESP32. It allows handling HTTP requests and WebSocket connections without blocking the main loop.
    - **Usage**: The `ESPAsyncWebServer` library is used to create a WebSocket server that clients can connect to in order to receive real-time pressure data.

3. **WiFi** (ESP8266WiFi for ESP8266)
    - **Purpose**: This library is used to manage Wi-Fi connections on the ESP32.
    - **Usage**: The `WiFi` library is used to set up the ESP32 as a Wi-Fi Access Point, allowing other devices to connect to it.

4. **AsyncTCP** (ESPAsyncTCP for ESP8266)
    - **Purpose**: This library provides an asynchronous TCP library for the ESP32, which is required by the `ESPAsyncWebServer` library.
    - **Usage**: The `AsyncTCP` library is used to handle TCP connections asynchronously, allowing for non-blocking communication in the WebSocket server.

## Configuration

### Wi-Fi Configuration

- **SSID**: `Uropine Device 1`
- **Password**: `rsi_12345`

These credentials are used to set up the ESP32 as a Wi-Fi Access Point. Devices can connect to this network to access the WebSocket server.

### Pin Configuration

- **Input Pin**: `34`

The ESP32 reads pressure data from the sensor connected to pin 34.

### WebSocket Server

- **Port**: `80`
- **Endpoint**: `/ws`

The WebSocket server listens on port 80 and uses the endpoint `/ws` for WebSocket connections.

### Serial Communication

- **Baud Rate**: `9600`

The ESP32 communicates with the USB serial monitor at a baud rate of 9600 for debugging purposes.

## How It Works

1. **Setup**:
    - The ESP32 is configured as a Wi-Fi Access Point.
    - A WebSocket server is started on port 80.
    - The input pin for the pressure sensor is initialized.

2. **Loop**:
    - The ESP32 reads pressure data from the sensor.
    - The data is formatted into a JSON object.
    - The JSON string is sent to all connected WebSocket clients.
    - The pressure data is also printed to the USB serial monitor.
    - The WebSocket server handles client connections and disconnections.
