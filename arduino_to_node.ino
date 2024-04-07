#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ONE_WIRE_BUS 4  // GPIO pin for DS18B20 sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define TDS_PIN 32

const char *ssid = "TP-Link_635B";
const char *password = "56263350";

const int potPin=A0;
float ph;
float pHValue=0;
float TDSValue=0;
float t=0;
WebServer server(80);

void handleRoot() {
char msg[1500];
snprintf(msg, 1500,
         "<html>\
<head>\
  <meta http-equiv='refresh' content='4'/>\
  <meta name='viewport' content='width=device-width, initial-scale=1'>\
  <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.2/css/all.css' integrity='sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr' crossorigin='anonymous'>\
  <title>Water Monitoring System</title>\
  <style>\
  html { font-family: Arial; display: inline-block; margin: 0px auto; text-align: center;}\
  h2 { font-size: 3.0rem; }\
  p { font-size: 3.0rem; }\
  .units { font-size: 1.2rem; }\
  .dht-labels{ font-size: 1.5rem; vertical-align:middle; padding-bottom: 15px;}\
  </style>\
</head>\
<body>\
    <h2>Water Monitoring System</h2>\
    <p>\
      <i class='fas fa-thermometer-half' style='color:#ca3517;'></i>\
      <span class='dht-labels'>Temperature</span>\
      <span>%.2f</span>\
      <sup class='units'>&deg;C</sup>\
    </p>\
    <p>\
      <i class='fas fa-tint' style='color:#00add6;'></i>\
      <span class='dht-labels'>TDS</span>\
      <span>%.2f</span>\
      <sup class='units'></sup>\
    </p>\
    <p>\
      <i class='fas fa-flask' style='color:#FFD700;'></i>\
      <span class='dht-labels'>pH</span>\
      <span>%.2f</span>\
    </p>\
</body>\
</html>",
         readTemperature(),
         readTDS(),
         readPh()
        );
server.send(200, "text/html", msg);
}

void setup(void) {
Serial.begin(115200);
sensors.begin();
pinMode(potPin,INPUT);


display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
display.clearDisplay();
display.setTextColor(SSD1306_WHITE);
display.setTextSize(1);
display.setCursor(0, 0);
display.println("TDS, pH, Temp");
display.display();
delay(2000);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
Serial.println("");
// Wait for connection
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}