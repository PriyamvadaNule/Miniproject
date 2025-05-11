# 👟 Smart Shoes for Visually Impaired

This project presents a wearable assistive device designed to enhance the mobility and safety of visually impaired individuals. The Smart Shoes system detects front and back obstacles, close-range hazards, and wet or slippery surfaces using various sensors and provides real-time feedback via vibration motors and buzzers.

---

## 🧠 Features

- Obstacle detection (front and back) using ultrasonic sensors
- Close-range detection using IR sensor
- Wet surface detection using soil moisture sensor
- Real-time haptic (vibration) and audio (buzzer) feedback
- Low power consumption and portable design
- Powered by ESP32 microcontroller

---

## 🔧 Components Used

| Component             | Quantity |
|----------------------|----------|
| ESP32 Dev Board       | 1        |
| Ultrasonic Sensor (HC-SR04) | 2        |
| IR Sensor             | 1        |
| Soil Moisture Sensor  | 1        |
| Vibration Motor (5V ERM) | 2    |
| Buzzer                | 2        |
| BC547 NPN Transistor  | 2        |
| Resistors (220Ω, 1kΩ) | As required |
| Diodes (1N4007)       | 2        |
| Lithium-ion Battery   | 1        |
| Zero PCB / Breadboard | 1        |
| Jumper Wires          | As required |

---

## 🛠️ Working Principle

1. **Sensors** continuously monitor the environment.
2. **ESP32** reads inputs and determines whether an obstacle or wet surface is present.
3. If a hazard is detected:
   - A **buzzer** activates for an audio alert.
   - A **vibration motor** vibrates to notify the user through haptic feedback.

---

## 🔌 Pin Configuration (ESP32)

| Sensor/Device       | ESP32 Pin        |
|---------------------|------------------|
| Front Ultrasonic TRIG | GPIO 4          |
| Front Ultrasonic ECHO | GPIO 5          |
| Back Ultrasonic TRIG  | GPIO 18         |
| Back Ultrasonic ECHO  | GPIO 19         |
| IR Sensor OUT        | GPIO 14          |
| Moisture Sensor AO   | GPIO 34 (Analog) |
| Buzzer 1             | GPIO 27          |
| Buzzer 2             | GPIO 17          |
| Vibration Motor 1    | GPIO 15          |
| Vibration Motor 2    | GPIO 16          |

---

## 💻 Software

- **Arduino IDE** – Programming ESP32
- **Tinkercad / Fritzing** – Circuit simulation and design
- **(Optional)** Proteus – Simulation testing

---

## 🔄 Future Enhancements

- App-based alerts via Wi-Fi (MQTT or Blynk)
- GPS integration for location tracking
- Voice assistant or audio direction guidance
- Rechargeable battery optimization
- AI-based smart obstacle recognition

---

## 📷 Project Preview

*Insert block diagram / circuit diagram / hardware images here*

---

## 👩‍💻 Authors

- **Priyamvada Nule** – T.Y. B.Tech (E&TC), Walchand Institute of Technology, Solapur

---

## 📄 License

This project is for educational and academic use only. Please credit the authors if reused or modified.
