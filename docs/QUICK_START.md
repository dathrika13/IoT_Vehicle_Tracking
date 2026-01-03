# 🚀 Quick Start Guide

Get your IoT Vehicle Tracking System up and running in 10 minutes!

---

## Step 1: Hardware Setup (5 minutes)

### Minimum Required Connections

```
NodeMCU          GPS Module (NEO-6M)
--------         ------------------
3.3V     ────────► VCC
GND      ────────► GND
D6       ◄────────  TX
D7       ────────►  RX
```

### Optional: LCD Display

```
NodeMCU          I2C LCD
--------         -------
VIN (5V) ────────► VCC
GND      ────────► GND
D2       ────────► SDA
D1       ────────► SCL
```

---

## Step 2: Software Setup (3 minutes)

### 2.1 Install Arduino IDE
Download from: https://www.arduino.cc/en/software

### 2.2 Add ESP8266 Board Support
1. Open Arduino IDE
2. `File` → `Preferences`
3. Add URL: `https://arduino.esp8266.com/stable/package_esp8266com_index.json`
4. `Tools` → `Board` → `Boards Manager` → Search "ESP8266" → Install

### 2.3 Install Libraries
`Sketch` → `Include Library` → `Manage Libraries`:
- TinyGPS++
- ThingSpeak
- LiquidCrystal_I2C

---

## Step 3: Configure & Upload (2 minutes)

### 3.1 Edit Credentials
Open `src/IoT_Vehicle_Tracking.ino` and modify:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
unsigned long ch_no = YOUR_THINGSPEAK_CHANNEL;
const char* write_api = "YOUR_API_KEY";
```

### 3.2 Upload
1. Connect NodeMCU via USB
2. Select: `Tools` → `Board` → `NodeMCU 1.0 (ESP-12E Module)`
3. Select correct COM port
4. Click Upload ▶️

---

## Step 4: Test It!

1. **Power on** the circuit
2. **Watch LCD** for WiFi connection status
3. **Note the IP address** shown on LCD
4. **Open browser** → Enter IP address
5. **Click link** to view location on Google Maps!

---

## 🆘 Quick Troubleshooting

| Problem | Solution |
|---------|----------|
| WiFi won't connect | Check SSID/password, ensure 2.4GHz network |
| GPS shows 0,0 | Go outdoors, wait 1-2 minutes |
| LCD blank | Check I2C address (0x27 or 0x3F) |
| Upload fails | Press FLASH button on NodeMCU while uploading |

---

## 📊 ThingSpeak Quick Setup

1. Go to https://thingspeak.com → Sign up
2. Click "New Channel"
3. Name: `Vehicle Tracker`
4. Field 1: `Latitude`
5. Field 2: `Longitude`
6. Save → Copy Channel ID and Write API Key

---

## ✅ Success Checklist

- [ ] NodeMCU connected and powered
- [ ] GPS module connected (outdoor for best signal)
- [ ] WiFi credentials configured
- [ ] ThingSpeak channel created
- [ ] Code uploaded successfully
- [ ] IP address displayed on LCD
- [ ] Web interface accessible
- [ ] Location visible on Google Maps

---

**Need more help?** Check the full [README.md](README.md) or open an issue!
