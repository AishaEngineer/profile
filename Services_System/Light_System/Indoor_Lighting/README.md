# 🏠 WiFi Indoor Smart Lighting System

## 📌 Overview
This project is part of a Smart Building Management System.
It implements a WiFi-based indoor lighting control system using Arduino Mega 2560 and ESP8266 (Access Point mode).

The system allows wireless ON/OFF control of indoor lights and appliances through a custom web interface.

---

## 🎯 Key Features
- WiFi-based control (Access Point Mode)
- ON/OFF toggle logic
- Web-based control panel
- Multi-room lighting control
- Fan control
- Door open / close control
- Real-time HTTP request handling

---

## 🛠 Hardware Components
- Arduino Mega 2560
- ESP8266 WiFi Module
- 8-Channel Relay Module
- AC Bulbs
- Fan
- Jumper Wires
- 5V Power Supply

---

## 💻 Software Technologies
- Arduino C++
- HTML
- CSS
- JavaScript (AJAX)
- AT Commands for ESP8266

---

## 🌐 How It Works

1. ESP8266 is configured as an Access Point (IP: 192.168.4.1).
2. The user connects to the ESP WiFi network.
3. The user opens the web interface.
4. When a button is pressed, an HTTP GET request is sent.
5. Arduino reads the request and toggles the corresponding relay.

---

## 🔌 Pin Mapping

| Device        | Command ID | Arduino Output Pin |
|--------------|------------|--------------------|
| Control Room | 40         | 25                 |
| Small Room   | 42         | 26                 |
| Living Room  | 46         | 7                  |
| Bathroom     | 43         | 22                 |
| Kitchen      | 44         | 23                 |
| Fan          | 49         | 28                 |

---

## 🏗 System Architecture

User (Web Browser)
        ↓
ESP8266 (Access Point)
        ↓
Arduino Mega 2560
        ↓
Relay Module
        ↓
Lights / Appliances

---

## 🚀 Future Improvements
- Add motion sensors (PIR)
- Add light sensors (LDR)
- Add mobile application control
- Real-time status feedback system
- Upgrade to standalone ESP firmware

---

## 👩‍💻 Author
Graduation Project – Electrical Engineering  
(Computer & Control Systems)
