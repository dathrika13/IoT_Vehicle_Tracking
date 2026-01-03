/*
 * CREDENTIALS TEMPLATE
 * ====================
 * 
 * Instructions:
 * 1. Copy this file and rename it to 'credentials.h'
 * 2. Fill in your actual credentials
 * 3. The credentials.h file is in .gitignore so it won't be uploaded to GitHub
 * 
 * IMPORTANT: Never commit your actual credentials to version control!
 */

#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// ============================================
// WiFi Configuration
// ============================================
#define WIFI_SSID     "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

// ============================================
// ThingSpeak Configuration
// ============================================
#define THINGSPEAK_CHANNEL_ID    123456           // Your Channel ID (number)
#define THINGSPEAK_WRITE_API_KEY "XXXXXXXXXXXXXXXX" // Your Write API Key

// ============================================
// Blynk Configuration (Optional)
// ============================================
#define BLYNK_AUTH_TOKEN "your_blynk_auth_token"

// ============================================
// GPS Configuration
// ============================================
#define GPS_RX_PIN D6
#define GPS_TX_PIN D7
#define GPS_BAUD   9600

// ============================================
// LCD Configuration
// ============================================
#define LCD_I2C_ADDRESS 0x27  // Try 0x3F if 0x27 doesn't work
#define LCD_COLUMNS     16
#define LCD_ROWS        2

// ============================================
// DHT Sensor Configuration
// ============================================
#define DHT_PIN  D4
#define DHT_TYPE DHT11

// ============================================
// Web Server Configuration
// ============================================
#define WEB_SERVER_PORT 80

// ============================================
// Update Intervals (in milliseconds)
// ============================================
#define THINGSPEAK_UPDATE_INTERVAL 20000  // 20 seconds (minimum 15 for free account)
#define GPS_READ_INTERVAL          1000   // 1 second
#define SENSOR_READ_INTERVAL       2000   // 2 seconds

#endif // CREDENTIALS_H
