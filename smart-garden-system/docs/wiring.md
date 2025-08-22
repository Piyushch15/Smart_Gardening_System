# Wiring Guide

## Quick Table
| Module | Signal | Arduino Pin |
|---|---|---|
| DHT11 | VCC | 5V |
| DHT11 | GND | GND |
| DHT11 | DATA | D2 |
| Soil Sensor | AO | A0 |
| Soil Sensor | VCC | 5V |
| Soil Sensor | GND | GND |
| Relay Module | IN | D7 |
| Relay Module | VCC | 5V |
| Relay Module | GND | GND |
| LCD 16x2 I²C | SDA | A4 (Uno/Nano) |
| LCD 16x2 I²C | SCL | A5 (Uno/Nano) |
| LCD 16x2 I²C | VCC | 5V |
| LCD 16x2 I²C | GND | GND |

> **Note on relay logic:** Many relay modules are *active-LOW*. If your pump behavior is inverted, swap `HIGH`/`LOW` in the code for `RELAY_PIN` (and ensure default state keeps the pump OFF).

## Power Notes
- Use a **separate power supply** for the pump (with sufficient current).  
- **Common ground** between Arduino, relay module, and pump supply.
- For inductive loads, use proper protection (flyback diode, snubber).

