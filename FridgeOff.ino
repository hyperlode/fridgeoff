#include "Button.h"

#define PIN_BUTTON_TRIGGER 8
#define PIN_RELAY 12

Button button_trigger;

#define RELAY_OFF HIGH // relayboard work with high = off.
#define RELAY_ON LOW


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
                                                        
    pinMode(PIN_RELAY, OUTPUT); // pull down resistors are not available...
    button_trigger.init(PIN_BUTTON_TRIGGER);

    digitalWrite(PIN_RELAY, RELAY_OFF); 
}
void loop() {
  // put your main code here, to run repeatedly:
   if (button_trigger.isPressedEdge()){
       Serial.println("pressed"); 
   }

   button_trigger.refresh();

   if (button_trigger.isPressedEdge()){
       digitalWrite(PIN_RELAY, RELAY_ON);
       
   }
    if (button_trigger.isUnpressedEdge()){
       digitalWrite(PIN_RELAY, RELAY_OFF);
      
   }
  
}
