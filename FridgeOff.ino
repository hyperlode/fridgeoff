#include "Button.h"
#include "SuperTimer.h"

#define PIN_BUTTON_TRIGGER 8
#define PIN_BUTTON_TEST 9
#define PIN_RELAY 12

Button button_trigger;
Button button_test;
SuperTimer timer_timeout;

#define RELAY_OFF HIGH // relayboard work with high = off.
#define RELAY_ON LOW

bool latchingButtonAsMomentaryButtonIsActive;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);

    pinMode(PIN_RELAY, OUTPUT); 
    button_trigger.init(PIN_BUTTON_TRIGGER); // LATCHING Button is used. But, it should have been a momentary push button
    button_test.init(PIN_BUTTON_TEST);

    digitalWrite(PIN_RELAY, RELAY_OFF);
    latchingButtonAsMomentaryButtonIsActive = false;
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (button_trigger.isPressedEdge())
    {
    }

    button_trigger.refresh();
    button_test.refresh();

    delay(10);

    // test button: hold to test timeout. release to instant switch off
    if (button_test.isPressedEdge())
    {
        digitalWrite(PIN_RELAY, RELAY_ON);
        timer_timeout.startCountDownWithSeconds(3);
        Serial.println("Relay ON: test");
    }
    if (button_test.isUnpressedEdge())
    {
        digitalWrite(PIN_RELAY, RELAY_OFF);
        Serial.println("Relay OFF: test");
    }

    if (button_trigger.isPressedEdge() || button_trigger.isUnpressedEdge())
    {
        if (latchingButtonAsMomentaryButtonIsActive)
        {
            digitalWrite(PIN_RELAY, RELAY_OFF);
            Serial.println("Relay OFF: triggered");
            latchingButtonAsMomentaryButtonIsActive = false;
        }
        else
        {
            Serial.println("Relay ON: triggered");
            digitalWrite(PIN_RELAY, RELAY_ON);
            timer_timeout.startCountDownWithSeconds(1800);
            latchingButtonAsMomentaryButtonIsActive = true;
        }
    }

    if (!timer_timeout.getTimeIsNegative())
    {
        Serial.println("Relay OFF: timed out");
        digitalWrite(PIN_RELAY, RELAY_OFF);
        timer_timeout.pause();
        latchingButtonAsMomentaryButtonIsActive = false;
    }
}
