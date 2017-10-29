#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#define FALSE 0
#define TRUE 1

// IO pin defines
#define BLUE 16     // D0 GPIO16
#define YELLOW 14   // D5 GPIO14
#define WHITE 15    // D8 GPIO15
#define PHOTOTRANSISTOR A0

WiFiServer server(80);
WiFiClient client;
String request;

/* Public variables */
const char* ssid = "Molk";
const char* password = "Molk0901";

/* Public functions */
void initWifi(void);
void initIO(void);
void runWeb(void);
