/*
 * Simons Bibliothek für das Projekt "Ampel"
 * Modul: Eingebettete Software
 */

#ifndef Trafficlight_h
#define Trafficlight_h

#include <Arduino.h>

class Trafficlight {
public:

	/**
	 * Konstruktor
	 *
	 * @param pin_red Pin, der das rote Licht symbolisiert
	 * @param pin_yellow Pin, der das gelbe Licht symbolisiert
	 * @param pin_red Pin, der das grüne Licht symbolisiert
	 * @param msForSecond Die Dauer einer Sekunde in Millisekunden.
	 * 			Geschwindikeit, in der die Ampel schalten soll
	 * 			(Mininum: 200, Maximum: 10000)
	 */
	Trafficlight(int pin_red, int pin_yellow, int pin_green, int msForSecond);

	/**
	 * Schaltet den normalen Modus an
	 */
	void wakeUp();

	/**
	 * Schaltet den Schlafmodus an
	 */
	void fallAsleep();

	/**
	 * Schaltet auf rot und dann wieder auf grün
	 */
	void stopAndGo();

	/**
	 * Animation, die die Lichter der Reihe nach anschaltet
	 */
	void animate();

private:

	int redPin;
	int yellowPin;
	int greenPin;
	int thisSec;

	unsigned long lastMillis;

	void init();

};

#endif
