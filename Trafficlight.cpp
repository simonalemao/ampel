/*
 * Simons Bibliothek für das Projekt "Ampel"
 * Modul: Eingebettete Software
 * 2020
 */

#include "Trafficlight.h"

Trafficlight::Trafficlight(int pin_red, int pin_yellow, int pin_green,
		int msForSecond, int redGreenDur) {
	redPin = pin_red;
	yellowPin = pin_yellow;
	greenPin = pin_green;

	pinMode(redPin, OUTPUT);
	pinMode(yellowPin, OUTPUT);
	pinMode(greenPin, OUTPUT);

	if (msForSecond == 0) {
		thisSec = 1000;
	} else if (msForSecond < 200) {
		thisSec = 200;
	} else if (msForSecond < 10000) {
		thisSec = msForSecond;
	} else {
		thisSec = 10000;
	}

	if (redGreenDur == 0) {
		thisSec = 5000;
	} else if (redGreenDur < 1000) {
		thisSec = 1000;
	} else if (redGreenDur < 30000) {
		thisSec = redGreenDur;
	} else {
		thisSec = 30000;
	}

	init();
}

void Trafficlight::init() {
	digitalWrite(redPin, LOW);
	digitalWrite(yellowPin, LOW);
	digitalWrite(greenPin, LOW);
}

void Trafficlight::stopGoStop() {
	// Start mit rot
	digitalWrite(redPin, HIGH);
	digitalWrite(yellowPin, LOW);
	digitalWrite(greenPin, LOW);
	delay(redGreenDur);

	// Rot-Gelb
	digitalWrite(yellowPin, HIGH);
	delay(2 * msForSecond);

	// Grün
	digitalWrite(greenPin, HIGH);
	digitalWrite(yellowPin, LOW);
	delay(redGreenDur);

	// Gelb
	digitalWrite(yellowPin, HIGH);
	digitalWrite(greenPin, LOW);
	delay(3 * msForSecond);

	// Rot
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

void Trafficlight::flash() {
	// Gelb
	digitalWrite(greenPin, LOW);
	digitalWrite(redPin, LOW);
	digitalWrite(yellowPin, HIGH);
	delay(thisSec);

	// Aus
	digitalWrite(yellowPin, LOW);
	delay(thisSec);
}
