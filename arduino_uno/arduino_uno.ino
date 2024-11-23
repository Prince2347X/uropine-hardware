/**
 * @file arduino_uno.ino
 * @brief This code reads data from a sensor and prints the values to the Serial Monitor.
 *
 * This code is specifically designed for the Arduino Uno board and was used in the very first version of our device.
 *
 * @details
 * - The sensor is connected to analog pin A0.
 * - The sensor data is read in the loop and printed to the Serial Monitor every 500 milliseconds.
 *
 * @note This code is being used with version 0.5 of our hardware. We have used a best fit
 * equation to plot the graph in the app. The equation is as follows:
 * cm of H₂O = 0.352 × (sensor value) − 135.67
 *
 * @note Ensure that the baud rate in the Serial Monitor is set to 9600 to match the Serial.begin(9600) setting.
 *
 * @author Prince Raj
 * @version 0.1
 * @date 2024-09-30
 */

#define SENSOR_PIN A0

int sensorData;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  sensorData = analogRead(SENSOR_PIN);
  Serial.println(sensorData);
  delay(500);
}