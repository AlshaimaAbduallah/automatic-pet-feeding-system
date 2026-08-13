# 🐾 Automatic Pet Feeding System

An embedded, microcontroller-based automatic pet feeder designed and simulated for the *Microprocessor System Design* course — Department of Electrical and Electronic Engineering, University of Khartoum. The system dispenses food at scheduled times, monitors remaining food level, and alerts the owner when a refill is needed, built around an Arduino Uno (ATmega328P).

> 🔗 **Live simulation:** [Run this project on Wokwi](https://wokwi.com/projects/471244750730611713)

---

## 📖 Overview

Pet owners often struggle to maintain a consistent feeding schedule due to unpredictable work hours, travel, or daily routines. This project addresses that problem with a low-cost, reliable embedded system that automates feeding, tracks food inventory, and requires minimal human intervention.

## ✨ Features

- ⏰ **Scheduled feeding** at 08:00 and 18:00 via a DS1307 Real-Time Clock (RTC) module
- 🎯 **Precise portion control** using a PWM-driven SG90 servo motor (0°–90° gate)
- 📏 **Food-level monitoring** with a non-contact HC-SR04 ultrasonic sensor (20 cm threshold)
- 🔔 **Visual & audible alerts** (buzzer + red LED) when food runs low
- 🖥️ **On-device UI** — 16×2 I²C LCD display + 4×4 matrix keypad for manual feeding
- 🛡️ **Duplicate-dispensing protection** via a software flag (`fedThisMinute`)
- 🧪 **Fully simulated** in [Wokwi](https://wokwi.com) — no physical hardware required to test

## 🧩 Hardware Components

| Component | Model | Function |
|---|---|---|
| Microcontroller | Arduino Uno R3 (ATmega328P) | Central processing unit |
| Real-Time Clock | DS1307 | Scheduling & timekeeping |
| Display | 16×2 LCD with I²C (PCF8574) | System status display |
| Actuator | SG90 Micro Servo | Food dispensing gate |
| Food-Level Sensor | HC-SR04 Ultrasonic | Remaining food monitoring |
| User Input | 4×4 Matrix Keypad | Manual feeding ('A' key) |
| Alerts | Active Buzzer + Red/Green LEDs | Audible/visual notifications |
| Power Supply | Regulated 5V / 2A Adapter | System power source |

Full component justification and trade-off analysis are available in [`/docs`](./docs).

## 🔌 Pin Configuration

| Arduino Pin | Connected Device | Function |
|---|---|---|
| D4, D7, D8, D10 | Keypad Rows | R1–R4 |
| D11, D12, A1, A2 | Keypad Columns | C1–C4 |
| D5 | HC-SR04 Echo | Distance measurement |
| D6 | HC-SR04 Trigger | Ultrasonic trigger |
| D9 | SG90 Servo | PWM control |
| A0 | Active Buzzer | Audio alert |
| A3 | Red LED | Low food indicator |
| A4 | LCD + RTC | I²C SDA (0x27 / 0x68) |
| A5 | LCD + RTC | I²C SCL |

## 🗂️ Repository Structure

```
├── src/
│   └── pet_feeder.ino              # Main Arduino sketch
├── docs/
│   └── G34-AutomaticPetFeedingSystem.pdf   # Full technical report
├── media/
│   ├── block_diagram.png           # System block diagram
│   ├── schematic.png               # Electronic schematic
│   └── flowchart.png               # Software flowchart
├── LICENSE
└── README.md
```

## 🚀 Getting Started

### Option 1 — Run the simulation (no hardware needed)
1. Open the [Wokwi project](https://wokwi.com/projects/471244750730611713)
2. Click ▶ **Run** to start the simulation
3. Interact with the keypad and observe the LCD, servo, and alerts in real time

### Option 2 — Run on physical hardware
1. Wire the components according to the [pin configuration](#-pin-configuration) above
2. Install the required libraries in Arduino IDE:
   ```
   Wire
   LiquidCrystal_I2C
   RTClib
   Servo
   Keypad
   ```
3. Upload `src/pet_feeder.ino` to the Arduino Uno

## 📊 Project Report

This repository includes the full academic report covering problem definition, objectives, system requirements, hardware architecture, circuit design, power supply analysis, software architecture, simulation testing, results, and cost analysis. See [`docs/G34-AutomaticPetFeedingSystem.pdf`](./docs/G34-AutomaticPetFeedingSystem.pdf).

## 👥 Authors — Group 34

- **Alshaima Abdullahi Mohmed Elbashir** — 194029
- **Mohamed Abubaker Elsir Gafar** — 204097

Supervised by **Dr. Magdi B. M. Amien**
University of Khartoum, Faculty of Engineering — August 2026

## 📄 License

This project is licensed under the MIT License — see the [LICENSE](./LICENSE) file for details.
