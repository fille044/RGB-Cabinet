#include "lib.h"


void setup() 
{
  // put your setup code here, to run once:
    Serial.begin(115200);
    delay(1500);

    initIO();
    initWifi();

    delay(1000);
}


void loop() 
{
  // put your main code here, to run repeatedly:
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
