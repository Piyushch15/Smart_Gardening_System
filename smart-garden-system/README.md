# Smart Garden System (Arduino)

A simple, reliable **automatic irrigation + environment monitor** built with Arduino.  
It reads **soil moisture**, **temperature**, and **humidity** (DHT11), shows live values on a **16x2 I²C LCD**, and turns a **water pump** on/off via a **relay** based on a moisture threshold.

> Built by **Piyush Channote (Piyushch15)**. MIT Licensed.

---

## ✨ Features
- Live LCD readout: Temperature (°C), Humidity (%), Soil Moisture (0–1023)
- Auto pump control with adjustable moisture threshold
- Serial Monitor logs for debugging
- Basic sensor fault handling (DHT read checks)
- Compact code that fits on Arduino Uno/Nano

---

## 🧰 Hardware
- Arduino Uno/Nano (5V)
- DHT11 Temperature & Humidity Sensor
- Soil Moisture Sensor (analog)
- 16x2 I²C LCD (typical address `0x27`)
- 5V Relay Module (to switch the pump)
- Water pump + separate power (5–12V, per pump spec)
- Jumper wires, breadboard or perfboard

> ⚠️ **Safety**: Pumps draw more current than the Arduino can provide. **Never power the pump from the Arduino 5V pin.** Use a separate supply, common GND, and proper relay wiring. Add a flyback diode if driving coils directly.

---

## 🧪 Wiring (quick view)
| Signal | Pin |
|---|---|
| DHT11 data | D2 |
| Soil Moisture (AO) | A0 |
| Relay IN | D7 |
| LCD SDA | A4 (Uno/Nano) |
| LCD SCL | A5 (Uno/Nano) |
| Power | 5V & GND (as needed) |

See **docs/wiring.md** for a detailed table and notes.

---

## 🧩 Libraries
Install these via **Arduino IDE → Tools → Manage Libraries**:
- **DHT sensor library** by Adafruit
- **Adafruit Unified Sensor** by Adafruit
- **LiquidCrystal I2C** (e.g., by Frank de Brabander)

---

## 🚀 Quick Start
1. Clone or download this repo.
2. Open **`src/SmartGardenSystem.ino`** in Arduino IDE.
3. Select your board & COM port.
4. Install the libraries above.
5. Upload to the Arduino.
6. Open **Serial Monitor** (9600 baud) to view logs.

---

## ⚙️ Configuration
- Adjust moisture threshold in code (default: `threshold = 700`).  
  Calibrate by reading **dry** and **fully wet** values on the Serial Monitor, then pick a number in between.
- LCD I²C address: change `0x27` to `0x3F` if your LCD shows nothing.
- Relay logic: some relays are **active-LOW**. If your pump inverts (ON when it should be OFF), invert the `HIGH/LOW` writes for `RELAY_PIN` as per your module.

---

## 📂 Project Structure
```
smart-garden-system/
├─ src/
│  └─ SmartGardenSystem.ino
├─ docs/
│  ├─ wiring.md
│  └─ assets/
├─ hardware/
│  └─ bom.csv
├─ .github/
│  └─ ISSUE_TEMPLATE/
│     ├─ bug_report.md
│     └─ feature_request.md
├─ .gitignore
├─ CONTRIBUTING.md
├─ CODE_OF_CONDUCT.md
├─ LICENSE
└─ README.md
```

---

## 🧑‍💻 How it Works (high level)
- Reads `temperature`, `humidity` from DHT11 and analog `soilMoistureValue` from A0.
- Displays values on the LCD (line 1: temp & humidity; line 2: moisture & pump state).
- If moisture is **below** your comfort level (i.e., sensor reading is **high** for resistive probes), the relay toggles the pump.

---

## 🐞 Troubleshooting
- **LCD blank**: try address `0x3F`, check SDA/SCL pins.
- **DHT Error!**: wiring, 5V, and library installation; add a small pull-up resistor on the DHT data line if needed.
- **Pump always ON/OFF**: your relay might be **active-LOW**; invert the `digitalWrite` logic for `RELAY_PIN`.
- **No moisture change**: calibrate sensor; avoid powering the analog probe continuously (for longevity).

---

## 🗺️ Roadmap
- Add RTC timestamped logs to SD card / serial
- Web dashboard (ESP8266/ESP32) + Blynk/HTTP
- Auto night-time watering lockout
- Non-blocking loop with millis()

---

## 🤝 Contributing
Issues and PRs are welcome! See **CONTRIBUTING.md** for style and commit guidelines.

---

## 📄 License
MIT © 2025 Piyush Channote

