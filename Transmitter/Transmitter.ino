#include "Arduino.h"
#include <avr/sleep.h>

#include "RCSwitch.h"

#define EQUIPMENT_ID 1

// class for 433 transmitter
RCSwitch rf433Switch = RCSwitch();

#define LED_PIN LED_BUILTIN
#define TX_PIN 10
#define EMITTER_POWER_PIN 9

// External pin interrupt
#define INT0_PIN 3 // INT0
#define INT1_PIN 2 // INT1
#define INT2_PIN 0 // INT2
#define INT3_PIN 1 // INT3
#define INT4_PIN 7 // INT4

void interrupt0ServiceRoutine() { /* rien en première approche réalisé dans la boucle */ }
void interrupt1ServiceRoutine() { /* rien en première approche */ }
void interrupt2ServiceRoutine() { /* rien en première approche */ }
void interrupt3ServiceRoutine() { /* rien en première approche */ }
void interrupt4ServiceRoutine() { /* rien en première approche */ }


class LedIndicator
{
public:
	LedIndicator( uint8_t pin ) { _pin = pin; digitalWrite(_pin, HIGH); }
	~LedIndicator() { digitalWrite(_pin, LOW); }
private:
	uint8_t _pin;
};

/**
 * Mise en sommeil de la carte
 */
void sleepPwrDown()
{
    // Configuration du type de sleep
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    // Autorisation du mode sleep
    sleep_enable();

    // Activation du mode sleep
    sleep_cpu();

    // CPU en mode sleep,
    // Attente de l'interruption INT0 qui réveillera le CPU

    // Désactivation du mode sleep
    sleep_disable();
}


// RCSwitch Blyss
// { 500, {  1, 14 }, {  1,  3 }, {  3,  1 }, false },
// setRepeatTransmit(15);

// Sonnerie
// Received 1155892691 = 0x44E585D3 / 32bit Protocol: 13
// Received 1449842067 = 0x566AD593 / 32bit Protocol: 13
static bool toggleRing = false;
void ring()
{
	toggleRing = true ? false : true;
	unsigned long msg;
	if (toggleRing)
	{
		msg = 1155892691;
	}
	else
	{
		msg = 1449842067;
	}
	rf433Switch.send(msg, 32);
}

// Changement sonnerie
// Received 3625157587 = 0xD81383D3 / 32bit Protocol: 13
// Received 2467091347 = 0x930CD393 / 32bit Protocol: 13
static bool toggleRingSwitch = false;
void ringSwitch()
{
	toggleRingSwitch = true ? false : true;
	unsigned long msg;
	if (toggleRingSwitch)
	{
		msg = 3625157587;
	}
	else
	{
		msg = 2467091347;
	}
	rf433Switch.send(msg, 32);
}

//The setup function is called once at startup of the sketch
void setup()
{
    // Entrée en mode Pull-up
    pinMode(INT0_PIN, INPUT_PULLUP);
    // Attachement d'une interruption sur front descendant/montant de INT0
    attachInterrupt(0, interrupt0ServiceRoutine, FALLING /*RISING*/ );

    // Entrée en mode Pull-up
    pinMode(INT1_PIN, INPUT_PULLUP);
    // Attachement d'une interruption sur front descendant/montant de INT1
    attachInterrupt(1, interrupt1ServiceRoutine, FALLING /*RISING*/ );

    // Entrée en mode Pull-up
    pinMode(INT2_PIN, INPUT_PULLUP);
    // Attachement d'une interruption sur front descendant/montant de INT2
    attachInterrupt(2, interrupt2ServiceRoutine, FALLING /*RISING*/ );

    // Entrée en mode Pull-up
    pinMode(INT3_PIN, INPUT_PULLUP);
    // Attachement d'une interruption sur front descendant/montant de INT3
    attachInterrupt(3, interrupt3ServiceRoutine, FALLING /*RISING*/ );

    // Entrée en mode Pull-up
    pinMode(INT4_PIN, INPUT_PULLUP);
    // Attachement d'une interruption sur front descendant/montant de INT4
    attachInterrupt(4, interrupt4ServiceRoutine, FALLING /*RISING*/ );

    // Commande de l'alimentation du module d'émission 433MHz
    pinMode(EMITTER_POWER_PIN, OUTPUT);
	// Coupe l'alimentation du module d'émission
	digitalWrite(EMITTER_POWER_PIN, LOW);
    // Configure le module d'émission 433MHz
    rf433Switch.enableTransmit(TX_PIN);
    // Blyss
    rf433Switch.setProtocol(13);
    rf433Switch.setRepeatTransmit(16);

    // Initialisation de la led témoin d'émission
	digitalWrite(LED_PIN, LOW);
}


// The loop function is called in an endless loop
void loop()
{
	// Mise en sommeil
	// sleepPwrDown();

	// Enter power down state with ADC and BOD module disabled.
    // Wake up when wake up pin is low.
    // LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

	// Traitement réalisé en cas de réveil
	// Alimente le module d'émission
	digitalWrite(EMITTER_POWER_PIN, HIGH);

	// Flash a light to show transmission/wake up
//	digitalWrite(LED_PIN, HIGH);

	if ( digitalRead(INT0_PIN) == LOW /*HIGH*/ ) { LedIndicator led(LED_PIN); ring(); }
	if ( digitalRead(INT1_PIN) == LOW /*HIGH*/ ) { LedIndicator led(LED_PIN); ringSwitch(); }
	if ( digitalRead(INT2_PIN) == LOW /*HIGH*/ ) { /* TODO */ }
	if ( digitalRead(INT3_PIN) == LOW /*HIGH*/ ) { /* TODO */ }
	if ( digitalRead(INT4_PIN) == LOW /*HIGH*/ ) { /* TODO */ }

	// Stop a light to show end of transmission
//	digitalWrite(LED_PIN, LOW);

	// Coupe l'alimentation du module d'émission
	digitalWrite(EMITTER_POWER_PIN, LOW);

	// Wait 500ms
//	delay(500);
}
