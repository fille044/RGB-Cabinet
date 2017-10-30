#include "init.h"


/* ------------------------------------------------------*/
/*
   Sets up inputs and outputs
*/
/* ------------------------------------------------------*/
void initIO(void)
{
    pinMode(BLUELED, OUTPUT);
    pinMode(REDLED, OUTPUT);
    pinMode(GREENLED, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(BLUELED, LOW);
    digitalWrite(REDLED, LOW);
    digitalWrite(GREENLED, LOW);
}
