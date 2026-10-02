# IoT-Based Smart Fan Automation

A low-cost smart fan system that can be controlled through a custom mobile web app and voice commands, built using ESP32, Firebase, and a motor driver for smooth speed regulation.


## 📖 Overview

Fans are among the most commonly used appliances in homes, offices and classrooms, but they are still mostly operated manually and run at fixed speeds, wasting electricity. This project automates a DC motor-driven fan using an ESP32 microcontroller, allowing it to be switched ON/OFF and have its speed adjusted remotely — through a custom Progressive Web App (PWA) as well as voice commands.

## ✨ Features

- 🔊 Voice control ("fan on", "fan off", "fan high/medium/low")
- 📱 Custom mobile web app (installable, works cross-platform)
- 🌀 Smooth speed control using PWM
- ☁️ Real-time sync via Firebase Realtime Database
- 🔌 Low-cost, beginner-friendly hardware

## 🏗️ System Architecture
<img width="665" height="276" alt="image" src="https://github.com/user-attachments/assets/3de3a070-060f-470e-bc28-caa07df13b51" />


## 🔧 Hardware Components

| Component | Specification |
|---|---|
| ESP32 DevKit V1 | Main controller, Wi-Fi |
| L298N Motor Driver | 2A, PWM speed control |
| DC Geared Motor | 12V, 100 RPM, metal gear |
| Fan Blade | Mounted on motor shaft |
| Power Supply | 12V (motor), 5V 3A (ESP32) |
| Breadboard, Jumper Wires | Prototyping |

## 💻 Software Stack

- **Firmware:** Arduino IDE (C++), HTTPClient library
- **Cloud Database:** Firebase Realtime Database
- **Frontend:** HTML, CSS, JavaScript (Progressive Web App)
- **Hosting:** Netlify
- **Voice Recognition:** Web Speech API (browser-based)

## ⚙️ How It Works

1. User gives a voice command or uses the app controls
2. The PWA updates the `power` / `speed` values in Firebase
3. ESP32 polls the Firebase database over Wi-Fi every ~1 second
4. ESP32 drives the L298N motor driver — IN1/IN2 set direction, PWM on ENA sets speed
5. The DC motor spins the fan blade accordingly
6. App reflects the live fan status

## 🔌 Wiring

| ESP32 Pin | L298N Pin |
|---|---|
| GPIO 18 | IN1 |
| GPIO 19 | IN2 |
| GPIO 21 | ENA |
| GND | GND |

Motor connects to L298N `OUT1` / `OUT2`. Motor power (12V) and ESP32 power (5V) are kept on separate supplies with a common GND.

## 🚀 Setup

1. Flash `esp32_firmware.ino` to the ESP32 via Arduino IDE (set your Wi-Fi credentials and Firebase URL)
2. Deploy the `/app` folder (PWA) to Netlify or any static host
3. Open the hosted link on your phone and "Add to Home Screen"
4. Power the circuit and control the fan via app or voice


