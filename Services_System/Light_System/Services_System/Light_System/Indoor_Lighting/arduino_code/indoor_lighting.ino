/*
  Indoor Smart Lighting System
  WiFi Based - Access Point Mode

  Controller: Arduino Mega 2560
  WiFi Module: ESP8266
*/

#include <SoftwareSerial.h>

/* ===================== PIN DEFINITIONS ===================== */

// Command IDs received from Web Interface
#define ROOM1        40
#define ROOM2        42
#define ROOM3        46
#define BATHROOM     43
#define KITCHEN      44
#define DOOR_CLOSE   47
#define DOOR_OPEN    48
#define FAN_DEVICE   49

// Relay Output Pins
#define LED1_PIN 25   // Control Room
#define LED2_PIN 26   // Small Room
#define LED3_PIN 24   // (Reserved)
#define LED4_PIN 22   // Bathroom
#define LED5_PIN 23   // Kitchen
#define LED6_PIN 7    // Living Room
#define LED7_PIN 28   // Fan

/* ===================== GLOBAL VARIABLES ===================== */

bool ledState[7] = {false, false, false, false, false, false, false};

#define RX_PIN 10
#define TX_PIN 11
#define DEBUG true

SoftwareSerial esp8266(RX_PIN, TX_PIN);

/* ===================== FUNCTION DECLARATION ===================== */
String sendData(String command, const int timeout, boolean debug);
void handleDevice(int pinNumber);
void toggleDevice(int index, int outputPin);

/* ===================== SETUP ===================== */

void setup() {

  Serial.begin(9600);
  esp8266.begin(9600);

  int outputPins[] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN, LED5_PIN, LED6_PIN, LED7_PIN};

  for (int i = 0; i < 7; i++) {
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], LOW);
  }

  // Configure ESP8266 as Access Point
  sendData("AT+RST\r\n", 2000, DEBUG);
  sendData("AT+CWMODE=2\r\n", 1000, DEBUG);     // AP Mode
  sendData("AT+CIFSR\r\n", 1000, DEBUG);       // Get IP
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);    // Multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // Start server on port 80
}

/* ===================== MAIN LOOP ===================== */

void loop() {

  if (esp8266.available()) {

    if (esp8266.find("+IPD,")) {

      delay(500);

      int connectionId = esp8266.read() - 48;

      esp8266.find("pin=");

      int pinNumber = (esp8266.read() - 48) * 10;
      pinNumber += (esp8266.read() - 48);

      handleDevice(pinNumber);

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId;
      closeCommand += "\r\n";

      sendData(closeCommand, 1000, DEBUG);
    }
  }
}

/* ===================== DEVICE HANDLER ===================== */

void handleDevice(int pinNumber) {

  switch (pinNumber) {

    case ROOM1:
      toggleDevice(0, LED1_PIN);
      break;

    case ROOM2:
      toggleDevice(1, LED2_PIN);
      break;

    case ROOM3:
      toggleDevice(5, LED6_PIN);
      break;

    case BATHROOM:
      toggleDevice(3, LED4_PIN);
      break;

    case KITCHEN:
      toggleDevice(4, LED5_PIN);
      break;

    case FAN_DEVICE:
      toggleDevice(6, LED7_PIN);
      break;
  }
}

void toggleDevice(int index, int outputPin) {

  ledState[index] = !ledState[index];
  digitalWrite(outputPin, ledState[index]);
}

/* ===================== ESP COMMUNICATION ===================== */

String sendData(String command, const int timeout, boolean debug) {

  String response = "";
  esp8266.print(command);

  long int time = millis();

  while ((time + timeout) > millis()) {
    while (esp8266.available()) {
      char c = esp8266.read();
      response += c;
    }
  }

  if (debug) {
    Serial.println(response);
  }

  return response;
}
