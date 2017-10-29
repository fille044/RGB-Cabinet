/* Includes */
#include <ESP8266WiFi.h>
#include <Servo.h>

#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

/* Defines */
// General definitions
#define FALSE 0
#define TRUE 1

// IO pin defines
#define BLUELED 16    // D0 GPIO16
#define YELLOWLED 5   // D5 GPIO14
#define WHITELED 15   // D8 GPIO15

#define PHOTORESISTOR A0

/* Public variables */
const char* ssid = "Malmsatter2_2,4GHz";
const char* password = "zcVvV1x1iyFCE4q6Ao8M";

WiFiServer server(80);
WiFiClient client;
String request;

int connectTimeOutCounter = 0;
int ModeState = 0;


/* ------------------------------------------------------*/
/*
   Sets up inputs and outputs
*/
/* ------------------------------------------------------*/
void initIO(void)
{
    pinMode(BLUELED, OUTPUT);
    pinMode(YELLOWLED, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(BLUELED, LOW);
    digitalWrite(YELLOWLED, LOW);
}


/* ------------------------------------------------------*/
/*
   Initialize the Wifi-communication.
   Connects to network "Molk" and prints out the device
   IP-adress in serial monitor.
*/
/* ------------------------------------------------------*/
void initWifi(void)
{
    // Connect to WiFi network
    Serial.println();
    Serial.println();
    delay(500);
    Serial.print("Connecting to ");
    Serial.println(ssid);
  
    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        connectTimeOutCounter++;
        if (connectTimeOutCounter > 30) {
            connectTimeOutCounter = 0;
            Serial.println("Connection has timed out, trying again");
            initWifi();
        }
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    for (int ix = 0; ix < 10; ix++) {
        digitalWrite(BLUELED, HIGH);
        delay(100);
        digitalWrite(BLUELED, LOW);
        delay(100);
    }
    // Start the server
    server.begin();
    Serial.println("Server started");
  
    // Print the IP address
    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
  
    Serial.println();
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.println("/");
    Serial.println("/");
}


/* ------------------------------------------------------*/
/*
   Handles the functions for wepage layout and request
*/
/* ------------------------------------------------------*/
void runWeb(void)
{
    handleRequest();
    handleLayout();
}


void setup()
{
    Serial.begin(115200);
    delay(1500);

    initIO();
    initWifi();

    delay(1000);
}


/* ------------------------------------------------------*/
/*
   Checks requests from webpage input and sets ModeState to
   corresponding value, between 0-3.
*/
/* ------------------------------------------------------*/
void handleRequest(void)
{
    // Match the request
    if (request.indexOf("/Auto") != -1) {
        ModeState = 0;
    }
    if (request.indexOf("/Open") != -1) {

        ModeState = 1;
    }
    if(request.indexOf("/Closed") != -1) {
        ModeState = 2;
    }
}



/* ------------------------------------------------------*/
/*
   Build webpage in HTML with variable ModeState
*/
/* ------------------------------------------------------*/
void handleLayout(void)
{
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><title>ConnectedBlinds</title></head>");
    client.println("<body>");
    client.println("Hello World");
    client.println("</body>");
    client.println("</html>");
    delay(1);
    Serial.println("Ready");
}


/* ------------------------------------------------------*/
/*
   Main loop for functionality
*/
/* ------------------------------------------------------*/
void loop()
{ 
    delay(20);
    int clientCounter = 0;
    // Check if a client has connected
    client = server.available();
    if (!client) {
        return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available()) {
        delay(1);
        clientCounter++;
        if (clientCounter > 500) {
          return;
        }
    }

    // Read the first line of the request
    request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    runWeb();

    delay(1);
    Serial.println("Ready");

}
