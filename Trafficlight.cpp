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

	actual_tf_status = RED;
}

void Trafficlight::stopGoStop(TF_Status startFrom) {
	// Start mit rot
	digitalWrite(redPin, HIGH);
	digitalWrite(yellowPin, LOW);
	digitalWrite(greenPin, LOW);
	actual_tf_status = RED;
	delay(redGreenDur);

	// Rot-Gelb
	digitalWrite(yellowPin, HIGH);
	actual_tf_status = RED_YELLOW;
	delay(2 * thisSec);

	// Grün
	digitalWrite(greenPin, HIGH);
	digitalWrite(yellowPin, LOW);
	digitalWrite(redPin, LOW);
	actual_tf_status = GREEN;
	delay(redGreenDur);

	// Gelb
	digitalWrite(yellowPin, HIGH);
	digitalWrite(greenPin, LOW);
	actual_tf_status = YELLOW;
	delay(3 * thisSec);

	// Rot
	digitalWrite(greenPin, HIGH);
	digitalWrite(redPin, LOW);
	digitalWrite(yellowPin, LOW);
	actual_tf_status = RED;
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

TF_Status Trafficlight::getTFStatus() {
	return actual_tf_status;
}

