#include "Arduino.h"

#include "RCSwitch.h"

// class for 433 receiver
RCSwitch rf433Switch = RCSwitch();

#define LED_PIN 13

#define RX_PIN 0 //PD0

class LedIndicator
{
public:
	LedIndicator( uint8_t pin ) { _pin = pin; digitalWrite(_pin, HIGH); }
	~LedIndicator() { digitalWrite(_pin, LOW); }
private:
	uint8_t _pin;
};

//The setup function is called once at startup of the sketch
void setup()
{
	// print fast to console
    Serial.begin(115200);

    // 433 receiver on interrupt
    rf433Switch.enableReceive(RX_PIN);
}

// The loop function is called in an endless loop
void loop()
{
	if( rf433Switch.available() )
	{
		// Turn on LED on to show that data has been received
		LedIndicator led(LED_PIN);

		// Display the received data on the debug serial line
	    Serial.print("Received ");
	    Serial.print( rf433Switch.getReceivedValue() );
	    Serial.print(" / ");
	    Serial.print( rf433Switch.getReceivedBitlength() );
	    Serial.print("bit ");
	    Serial.print("Protocol: ");
	    Serial.println( rf433Switch.getReceivedProtocol() );

		// This should be called right after receiving data
		rf433Switch.resetAvailable();

		// Turn the led off
	}
}
