# Ultrasonic Distance Meter using PIC Microcontroller

A simple non-contact distance measuring system using a PIC16F877A microcontroller and an HC-SR04 ultrasonic sensor. The measured distance is displayed on a 16x2 LCD, with optional buzzer alerts for threshold-based detection.

---

## 📦 Features

- Accurate distance measurement using ultrasonic waves
- 16x2 LCD display output
- Optional buzzer for proximity alerts
- Configurable threshold
- Lightweight code compatible with XC8 and MPLAB X

---

## 🛠️ Components Required

| Component                    | Description               |
|-----------------------------|---------------------------|
| PIC16F877A                  | Microcontroller           |
| HC-SR04                     | Ultrasonic Distance Sensor|
| 16x2 LCD                    | Display                   |
| Buzzer (optional)           | Sound alert               |
| LM7805                      | Voltage regulator         |
| Resistors, Capacitors, Diodes| Supporting circuitry     |
| Breadboard or PCB           | For prototyping           |
| Power Supply (5V)           | System power              |
| Wires                       | Connections               |

---

## 🔌 Circuit Connections

### Ultrasonic Sensor (HC-SR04)
- VCC → 5V  
- GND → GND  
- Trig → RD0  
- Echo → RD1  

### LCD (16x2)
- Connected in 4-bit mode to GPIO  
- RS, EN → GPIO pins  
- D4–D7 → Data lines  

### Buzzer (Optional)
- Connect to RB0 or any digital output pin

---

## ⚙️ Working Principle

1. The microcontroller sends a 10µs pulse to the Trig pin.
2. The HC-SR04 emits an ultrasonic burst.
3. Echo pin goes HIGH and stays HIGH until echo is received.
4. The duration of the HIGH signal is used to calculate distance.
5. Distance is displayed on the LCD. If it’s below a threshold, the buzzer alerts.

**Distance formula:**

```text
Distance (cm) = (Time × Speed of Sound) / 2
Speed of sound = 343 m/s
