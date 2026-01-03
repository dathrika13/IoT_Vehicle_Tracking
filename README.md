# Autonomous Vehicle Tracking and Monitoring Using IoT

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/Platform-NodeMCU%20ESP8266-blue.svg)](https://www.nodemcu.com/)
[![IoT](https://img.shields.io/badge/IoT-ThingSpeak-green.svg)](https://thingspeak.com/)
[![Arduino](https://img.shields.io/badge/Arduino-IDE-teal.svg)](https://www.arduino.cc/)

An IoT-based solution for real-time vehicle tracking and environmental monitoring, designed for agricultural applications. This system uses GPS to track vehicle location and transmits data to the cloud for visualization and analysis.

![Project Banner](docs/images/banner.png)

---

## Table of Contents

- [About The Project](#about-the-project)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
- [ThingSpeak Setup](#thingspeak-setup)
- [Project Structure](#project-structure)
- [Screenshots](#screenshots)
- [Troubleshooting](#troubleshooting)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)
- [Author](#author)
- [Acknowledgments](#acknowledgments)

---

## About The Project

In agricultural environments, heavy vehicles like harvesters and tractors are essential for farming operations. This IoT-based system enables:

- **Real-time GPS tracking** of vehicle location
- **Environmental monitoring** (temperature & humidity)
- **Cloud-based data storage** and visualization
- **Web interface** for live location viewing on Google Maps
- **Remote monitoring** capabilities

The system uses NodeMCU (ESP8266) as the main microcontroller, which connects to the internet via Wi-Fi and sends GPS coordinates to the ThingSpeak cloud platform.

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 📍 **GPS Tracking** | Real-time location tracking using NEO-6M GPS module |
| 🌡️ **Environmental Monitoring** | Temperature and humidity sensing with DHT11 |
| ☁️ **Cloud Integration** | Data logging and visualization on ThingSpeak |
| 🌐 **Web Interface** | Built-in web server for live location access |
| 🗺️ **Google Maps Integration** | One-click access to vehicle location on maps |
| 📱 **Mobile Compatible** | Responsive web interface works on all devices |
| 📊 **Data Analytics** | Historical data visualization and analysis |
| 🔋 **Battery Powered** | Portable operation with Li-ion batteries |

---

## Hardware Requirements

| Component | Quantity | Description |
|-----------|----------|-------------|
| NodeMCU ESP8266 | 1 | Main microcontroller with Wi-Fi |
| NEO-6M GPS Module | 1 | GPS receiver for location tracking |
| DHT11 Sensor | 1 | Temperature and humidity sensor |
| L293D Motor Driver | 1 | DC motor controller IC |
| BO Motors | 4 | Battery operated DC geared motors |
| 16x2 LCD with I2C | 1 | Display module |
| Li-ion Battery (3.7V) | 3 | Power supply (connected in series) |
| Jumper Wires | As needed | For connections |
| Breadboard | 1 | For prototyping (optional) |
| Chassis | 1 | Vehicle body (optional) |

---

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software) (v1.8.x or later)
- [ThingSpeak Account](https://thingspeak.com/) (Free)
- [Blynk App](https://blynk.io/) (Optional - for mobile control)

### Required Libraries

Install these libraries via Arduino IDE Library Manager:

```
- TinyGPS++ (by Mikal Hart)
- ThingSpeak (by MathWorks)
- ESP8266WiFi (included with ESP8266 board package)
- LiquidCrystal_I2C (by Frank de Brabander)
- Wire (built-in)
- SoftwareSerial (built-in)
```

---

## Circuit Diagram

### Pin Connections

```
┌─────────────────────────────────────────────────────────────┐
│                     CIRCUIT CONNECTIONS                      │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  NodeMCU ESP8266          NEO-6M GPS Module                 │
│  ┌──────────────┐         ┌──────────────┐                  │
│  │              │         │              │                  │
│  │  3.3V ───────┼────────►│ VCC          │                  │
│  │  GND  ───────┼────────►│ GND          │                  │
│  │  D6   ◄──────┼─────────│ TX           │                  │
│  │  D7   ───────┼────────►│ RX           │                  │
│  │              │         │              │                  │
│  └──────────────┘         └──────────────┘                  │
│                                                              │
│  NodeMCU ESP8266          I2C LCD (16x2)                    │
│  ┌──────────────┐         ┌──────────────┐                  │
│  │              │         │              │                  │
│  │  VIN (5V) ───┼────────►│ VCC          │                  │
│  │  GND  ───────┼────────►│ GND          │                  │
│  │  D2   ───────┼────────►│ SDA          │                  │
│  │  D1   ───────┼────────►│ SCL          │                  │
│  │              │         │              │                  │
│  └──────────────┘         └──────────────┘                  │
│                                                              │
│  NodeMCU ESP8266          DHT11 Sensor                      │
│  ┌──────────────┐         ┌──────────────┐                  │
│  │              │         │              │                  │
│  │  3.3V ───────┼────────►│ VCC          │                  │
│  │  GND  ───────┼────────►│ GND          │                  │
│  │  D4   ◄──────┼─────────│ DATA         │                  │
│  │              │         │              │                  │
│  └──────────────┘         └──────────────┘                  │
│                                                              │
└─────────────────────────────────────────────────────────────┘
```

### Power Supply Configuration

```
Battery Configuration (Series Connection):
┌─────────┐   ┌─────────┐   ┌─────────┐
│ 3.7V    │───│ 3.7V    │───│ 3.7V    │──► ~11.1V Output
│ Li-ion  │   │ Li-ion  │   │ Li-ion  │
└─────────┘   └─────────┘   └─────────┘
```

---

## Installation

### Step 1: Set Up Arduino IDE for ESP8266

1. Open Arduino IDE
2. Go to `File` → `Preferences`
3. Add to "Additional Board Manager URLs":
   ```
   https://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
4. Go to `Tools` → `Board` → `Boards Manager`
5. Search for "ESP8266" and install the latest version
6. Select `Tools` → `Board` → `NodeMCU 1.0 (ESP-12E Module)`

### Step 2: Install Required Libraries

1. Go to `Sketch` → `Include Library` → `Manage Libraries`
2. Search and install:
   - `TinyGPS++`
   - `ThingSpeak`
   - `LiquidCrystal_I2C`

### Step 3: Clone the Repository

```bash
git clone https://github.com/yourusername/iot-vehicle-tracking.git
cd iot-vehicle-tracking
```

### Step 4: Upload the Code

1. Open `src/IoT_Vehicle_Tracking.ino` in Arduino IDE
2. Configure your credentials (see [Configuration](#configuration))
3. Connect NodeMCU via USB
4. Select the correct COM port
5. Click Upload

---

## ⚙️ Configuration

Edit the following variables in the code before uploading:

```cpp
// WiFi Credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ThingSpeak Credentials
unsigned long ch_no = YOUR_CHANNEL_NUMBER;
const char* write_api = "YOUR_WRITE_API_KEY";
```

---

## Usage

1. **Power on** the circuit
2. Wait for **WiFi connection** (IP address displayed on LCD)
3. **GPS Fix**: Wait for GPS module to acquire satellite signals
4. **Access Web Interface**: Open browser and navigate to the IP address shown on LCD
5. **View Location**: Click the link to open Google Maps with current location
6. **Monitor Data**: Check ThingSpeak channel for historical data and graphs

---

## ThingSpeak Setup

1. Create account at [thingspeak.com](https://thingspeak.com)
2. Click **"New Channel"**
3. Configure channel:
   - **Name**: Vehicle Tracking System
   - **Field 1**: Latitude
   - **Field 2**: Longitude
   - **Field 3**: Temperature (optional)
   - **Field 4**: Humidity (optional)
4. Save and note down:
   - **Channel ID** (from channel page)
   - **Write API Key** (from API Keys tab)

---

## Project Structure

```
iot-vehicle-tracking/
│
├── 📁 src/
│   └── IoT_Vehicle_Tracking.ino    # Main Arduino sketch
│
├── 📁 docs/
│   ├── 📁 images/
│   │   ├── banner.png
│   │   ├── circuit_diagram.png
│   │   ├── thingspeak_setup.png
│   │   └── web_interface.png
│   │
│   ├── IoT_Vehicle_Tracking_Documentation.pdf
│   └── IoT_Vehicle_Tracking_Documentation.docx
│
├── 📁 hardware/
│   ├── circuit_schematic.fzz       # Fritzing schematic
│   └── BOM.csv                     # Bill of Materials
│
├── 📁 libraries/
│   └── TinyGPSPlus/                # Library backup (optional)
│
├── .gitignore
├── LICENSE
├── CONTRIBUTING.md
└── README.md
```

---

## Screenshots

### ThingSpeak Dashboard
![ThingSpeak Dashboard](docs/images/thingspeak_dashboard.png)

### Web Interface
![Web Interface](docs/images/web_interface.png)

### Hardware Setup
![Hardware Setup](docs/images/hardware_setup.png)

---

## 🔍 Troubleshooting

| Issue | Solution |
|-------|----------|
| **WiFi not connecting** | Verify SSID/password; Ensure 2.4GHz network (ESP8266 doesn't support 5GHz) |
| **GPS not getting fix** | Move outdoors with clear sky view; Wait 1-2 minutes for cold start |
| **LCD not displaying** | Check I2C address (try 0x27 or 0x3F); Verify SDA/SCL connections |
| **ThingSpeak errors** | Verify Channel ID and API Key; Ensure 15+ second delay between updates |
| **No serial output** | Set baud rate to 115200 in Serial Monitor |
| **GPS showing 0.000000** | GPS needs time to acquire satellites; Check antenna connection |

---

## 🔮 Future Enhancements

- [ ] **LoRa Integration** - Long-range communication without WiFi
- [ ] **Solar Power** - Sustainable power supply
- [ ] **Additional Sensors** - Fuel level, speed, engine diagnostics
- [ ] **Mobile App** - Dedicated Android/iOS application
- [ ] **Geofencing** - Alert when vehicle leaves designated area
- [ ] **Machine Learning** - Predictive maintenance using collected data
- [ ] **OTA Updates** - Over-the-air firmware updates
- [ ] **Multiple Vehicle Support** - Fleet management capabilities

---

## 🤝 Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---

## 📄 License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.

---

## 👩‍💻 Author

**Saicharitha Dathrika**

- Project Created: May 21, 2021
- GitHub: [@saicharithadathrika](https://github.com/saicharithadathrika)

---

## 🙏 Acknowledgments

- [TinyGPS++ Library](https://github.com/mikalhart/TinyGPSPlus) by Mikal Hart
- [ThingSpeak](https://thingspeak.com/) by MathWorks
- [ESP8266 Community](https://github.com/esp8266/Arduino)
- [Arduino](https://www.arduino.cc/)

---

<p align="center">
  Made with ❤️ for IoT enthusiasts
  <br>
  ⭐ Star this repository if you found it helpful!
</p>
