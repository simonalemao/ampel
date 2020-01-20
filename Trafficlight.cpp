/**
 * Trafficlight.cpp - Simons Bibliothek für das Projekt "Ampel"
 * Modul: Eingebettete Software
 * 2020
 */

#include "Trafficlight.h"

Trafficlight::Trafficlight(int pin_red, int pin_yellow, int pin_green,
		int msForSecond, int msForRedAndGreen) {
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

	if (msForRedAndGreen == 0) {
		redGreenDur = 5000;
	} else if (msForRedAndGreen < 1000) {
		redGreenDur = 1000;
	} else if (msForRedAndGreen < 30000) {
		redGreenDur = msForRedAndGreen;
	} else {
		redGreenDur = 30000;
	}

	next_tf_status = 0;

	cont = true;
}

void Trafficlight::stopGoStop() {
	if (next_tf_status == 0) {
		// Start mit rot
		digitalWrite(redPin, HIGH);
		digitalWrite(yellowPin, LOW);
		digitalWrite(greenPin, LOW);
		delay(redGreenDur);
		next_tf_status = cont ? 1 : 0;
	}

	// Rot-Gelb
	if (next_tf_status == 1) {
		digitalWrite(yellowPin, HIGH);
		delay(2 * thisSec);
		next_tf_status = cont ? 2 : 1;
	}

	// Grün
	if (next_tf_status == 2) {
		digitalWrite(greenPin, HIGH);
		digitalWrite(yellowPin, LOW);
		digitalWrite(redPin, LOW);
		delay(redGreenDur);
		next_tf_status = cont ? 3 : 2;
	}

	// Gelb
	if (next_tf_status == 3) {
		digitalWrite(yellowPin, HIGH);
		digitalWrite(greenPin, LOW);
		delay(3 * thisSec);
		next_tf_status = cont ? 0 : 3;
	}
}

void Trafficlight::animate() {
	int count = 0;
	while (count < 10) {

		digitalWrite(redPin, HIGH);
		delay(100);
		digitalWrite(redPin, LOW);
		digitalWrite(yellowPin, HIGH);
		delay(100);
		digitalWrite(yellowPin, LOW);
		digitalWrite(greenPin, HIGH);
		delay(100);
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

void Trafficlight::setContinue(bool b) {
	cont = b;
}

bool Trafficlight::getContinue() {
	return cont;
}

