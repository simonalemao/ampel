/*
 * Simons Bibliothek für das Projekt "Ampel"
 * Modul: Eingebettete Software
 */

#include "Trafficlight.h"

Trafficlight::Trafficlight(int pin_red, int pin_yellow, int pin_green,
		int msForSecond) {
	redPin = pin_red;
	yellowPin = pin_yellow;
	greenPin = pin_green;

	pinMode(redPin, OUTPUT);
	pinMode(yellowPin, OUTPUT);
	pinMode(greenPin, OUTPUT);

	if (msForSecond < 200) {
		thisSec = 200;
	} else if (msForSecond < 10000) {
		thisSec = msForSecond;
	} else {
		thisSec = 10000;
	}

	init();
}

void Trafficlight::init() {
	digitalWrite(redPin, LOW);
	digitalWrite(yellowPin, LOW);
	digitalWrite(greenPin, LOW);
}

void Trafficlight::wakeUp() {
	// Start mit grün
	digitalWrite(redPin, LOW);
	digitalWrite(yellowPin, LOW);
	digitalWrite(greenPin, HIGH);
}

void Trafficlight::fallAsleep() {

}

void Trafficlight::stopAndGo() {
	// Start mit grün
	digitalWrite(redPin, LOW);
	digitalWrite(yellowPin, LOW);
	digitalWrite(greenPin, HIGH);
	delay(1 * msForSecond);

	// Gelb
	digitalWrite(yellowPin, HIGH);
	digitalWrite(greenPin, LOW);
	delay(3 * msForSecond);

	// Rot
	digitalWrite(redPin, HIGH);
	digitalWrite(yellowPin, LOW);
	delay(5 * msForSecond);

	// Rot-Gelb
	digitalWrite(yellowPin, HIGH);
	delay(2 * msForSecond);

	// Grün
	digitalWrite(greenPin, HIGH);
	digitalWrite(redPin, LOW);
	digitalWrite(yellowPin, LOW);

}

void Trafficlight::animate() {
	int count = 0;
	while (count < 10) {

		digitalWrite(redPin, HIGH);
		delay(150);
		digitalWrite(redPin, LOW);
		digitalWrite(yellowPin, HIGH);
		delay(150);
		digitalWrite(yellowPin, LOW);
		digitalWrite(greenPin, HIGH);
		delay(150);
		digitalWrite(greenPin, LOW);

		count++;
	}
}
