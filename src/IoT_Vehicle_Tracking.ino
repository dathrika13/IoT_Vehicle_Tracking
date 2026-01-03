/*
 * AUTONOMOUS VEHICLE TRACKING AND MONITORING USING IoT
 * =====================================================
 * 
 * This Arduino sketch implements an IoT-based vehicle tracking system
 * using NodeMCU (ESP8266), GPS module, and ThingSpeak cloud platform.
 * 
 * Hardware Required:
 * - NodeMCU ESP8266
 * - NEO-6M GPS Module
 * - DHT11 Temperature & Humidity Sensor
 * - 16x2 LCD with I2C Module
 * - L293D Motor Driver
 * - BO Motors (4 units)
 * - Lithium-ion Batteries
 * 
 * Libraries Required:
 * - TinyGPS++ (https://github.com/mikalhart/TinyGPSPlus)
 * - ThingSpeak
 * - ESP8266WiFi
 * - LiquidCrystal_I2C
 * - Wire
 * 
 * Author: Saicharitha Dathrika
 * Date: May 21, 2021
 * Version: 1.0
 */

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// ============================================
// CONFIGURATION - Modify these values
// ============================================

// LCD Configuration (I2C Address, Columns, Rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// GPS Module Connection Pins
static const int RX = D6;
static const int TX = D7;
static const uint32_t GPSBaud = 9600;

// WiFi Credentials - CHANGE THESE
const char* ssid = "admin";           // Your WiFi Network SSID
const char* password = "12345678";    // Your WiFi Network Password

// ThingSpeak Credentials - CHANGE THESE
unsigned long ch_no = 12345;          // Your ThingSpeak Channel Number
const char* write_api = "ZS6XXXXXXXXXXXX";  // Your ThingSpeak Write API Key

// ============================================
// GLOBAL OBJECTS AND VARIABLES
// ============================================

// GPS object
TinyGPSPlus gps;

// WiFi client object
WiFiClient client;

// Web server on port 80
WiFiServer server(80);

// Software serial for GPS communication
SoftwareSerial soft(RX, TX);

// GPS coordinate strings
String latitude_data;
String longitude_data;

// ============================================
// SETUP FUNCTION
// ============================================

void setup() {
  // Initialize I2C communication
  Wire.begin(D2, D1);
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  
  // Display welcome message
  lcd.setCursor(0, 0);
  lcd.print("   IOT BASED   ");
  lcd.setCursor(0, 1);
  lcd.print("VEHICLE TRACKING");
  delay(2000);
  lcd.clear();
  
  // Initialize Serial for debugging
  Serial.begin(115200);
  Serial.println();
  Serial.println("IoT Vehicle Tracking System");
  Serial.println("===========================");
  
  // Initialize GPS software serial
  soft.begin(GPSBaud);
  Serial.println("GPS Module Initialized");
  
  // Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  server.begin();
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.setCursor(0, 0);
    lcd.print("WiFi connecting");
    lcd.setCursor(0, 1);
    lcd.print("Please wait...");
  }
  
  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected!");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  
  // Initialize ThingSpeak
  ThingSpeak.begin(client);
  Serial.println("ThingSpeak Initialized");
  
  delay(2000);
}

// ============================================
// MAIN LOOP
// ============================================

void loop() {
  // Process GPS data
  while (soft.available() > 0) {
    if (gps.encode(soft.read())) {
      displaydata();
      displaywebpage();
    }
  }
  
  // Check for GPS connection errors
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("GPS Connection Error!!"));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GPS Error!");
    lcd.setCursor(0, 1);
    lcd.print("Check wiring...");
    while (true);  // Halt execution
  }
}

// ============================================
// GPS DATA PROCESSING AND THINGSPEAK UPLOAD
// ============================================

void displaydata() {
  if (gps.location.isValid()) {
    // Get GPS coordinates
    double latitude = gps.location.lat();
    double longitude = gps.location.lng();
    
    // Convert to strings with 6 decimal places
    latitude_data = String(latitude, 6);
    longitude_data = String(longitude, 6);
    
    // Debug output
    Serial.println("=== GPS Data ===");
    Serial.print("Latitude: ");
    Serial.println(latitude_data);
    Serial.print("Longitude: ");
    Serial.println(longitude_data);
    
    // Update LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lat:");
    lcd.print(latitude_data.substring(0, 10));
    lcd.setCursor(0, 1);
    lcd.print("Lng:");
    lcd.print(longitude_data.substring(0, 10));
    
    // Send data to ThingSpeak
    ThingSpeak.setField(1, latitude_data);
    ThingSpeak.setField(2, longitude_data);
    
    int response = ThingSpeak.writeFields(ch_no, write_api);
    
    if (response == 200) {
      Serial.println("ThingSpeak update successful!");
    } else {
      Serial.print("ThingSpeak error: ");
      Serial.println(response);
    }
    
    // ThingSpeak requires minimum 15 seconds between updates
    delay(20000);
  } else {
    Serial.println("Waiting for valid GPS data...");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Searching GPS...");
    lcd.setCursor(0, 1);
    lcd.print("Please wait...");
  }
}

// ============================================
// WEB PAGE FOR LIVE LOCATION
// ============================================

void displaywebpage() {
  WiFiClient webclient = server.available();
  
  if (!webclient) {
    return;
  }
  
  Serial.println("New web client connected");
  
  // Wait for client to send request
  while (webclient.connected() && !webclient.available()) {
    delay(1);
  }
  
  // Read the request (and discard it)
  String request = webclient.readStringUntil('\r');
  Serial.println(request);
  webclient.flush();
  
  // Build HTML page
  String page = "<!DOCTYPE html>";
  page += "<html>";
  page += "<head>";
  page += "<meta charset='UTF-8'>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<title>Vehicle Tracking System</title>";
  page += "<style>";
  page += "body { font-family: Arial, sans-serif; margin: 0; padding: 20px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); min-height: 100vh; }";
  page += ".container { max-width: 600px; margin: 0 auto; background: white; padding: 30px; border-radius: 15px; box-shadow: 0 10px 40px rgba(0,0,0,0.2); }";
  page += "h1 { color: #333; text-align: center; margin-bottom: 30px; }";
  page += ".data { background: #f8f9fa; padding: 15px; border-radius: 8px; margin: 15px 0; }";
  page += ".data-label { font-weight: bold; color: #666; }";
  page += ".data-value { font-size: 1.2em; color: #333; }";
  page += ".btn { display: block; width: 100%; padding: 15px; background: #e74c3c; color: white; text-align: center; text-decoration: none; border-radius: 8px; font-size: 1.1em; margin-top: 20px; transition: background 0.3s; }";
  page += ".btn:hover { background: #c0392b; }";
  page += "</style>";
  page += "</head>";
  page += "<body>";
  page += "<div class='container'>";
  page += "<h1>🚗 Real Time Vehicle Tracking</h1>";
  page += "<div class='data'>";
  page += "<span class='data-label'>Latitude:</span><br>";
  page += "<span class='data-value'>" + latitude_data + "</span>";
  page += "</div>";
  page += "<div class='data'>";
  page += "<span class='data-label'>Longitude:</span><br>";
  page += "<span class='data-value'>" + longitude_data + "</span>";
  page += "</div>";
  page += "<a class='btn' href='http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
  page += latitude_data;
  page += "+";
  page += longitude_data;
  page += "' target='_blank'>📍 View Live Location on Google Maps</a>";
  page += "</div>";
  page += "</body>";
  page += "</html>";
  
  // Send HTTP response
  webclient.println("HTTP/1.1 200 OK");
  webclient.println("Content-Type: text/html");
  webclient.println("Connection: close");
  webclient.println();
  webclient.print(page);
  
  delay(100);
  webclient.stop();
  Serial.println("Web client disconnected");
}

/*
 * ============================================
 * CIRCUIT CONNECTIONS
 * ============================================
 * 
 * NodeMCU to GPS Module (NEO-6M):
 * - VCC  -> 3.3V
 * - GND  -> GND
 * - TX   -> D6 (RX on NodeMCU)
 * - RX   -> D7 (TX on NodeMCU)
 * 
 * NodeMCU to I2C LCD:
 * - VCC  -> VIN (5V)
 * - GND  -> GND
 * - SDA  -> D2
 * - SCL  -> D1
 * 
 * NodeMCU to L293D Motor Driver:
 * - Enable pins and input pins as per your motor control requirements
 * 
 * Power Supply:
 * - 3x 3.7V Li-ion batteries in series (~11.1V)
 * - Use voltage regulator for components requiring 5V or 3.3V
 * 
 * ============================================
 * TROUBLESHOOTING
 * ============================================
 * 
 * 1. WiFi not connecting:
 *    - Verify SSID and password
 *    - Ensure 2.4GHz network (ESP8266 doesn't support 5GHz)
 *    - Check signal strength
 * 
 * 2. GPS not getting fix:
 *    - Move to outdoor location with clear sky view
 *    - Wait 1-2 minutes for cold start
 *    - Check antenna connection
 * 
 * 3. ThingSpeak errors:
 *    - Verify Channel ID and API Key
 *    - Ensure minimum 15 second delay between updates
 *    - Check internet connectivity
 * 
 * 4. LCD not displaying:
 *    - Check I2C address (use I2C scanner sketch)
 *    - Verify SDA/SCL connections
 *    - Adjust contrast potentiometer on LCD module
 */
