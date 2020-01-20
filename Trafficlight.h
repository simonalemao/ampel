/**
 * Trafficlight.h - Simons Bibliothek für das Projekt "Ampel"
 * Modul: Eingebettete Software
 * 2020
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
	 * 			(Mininum: 200, Maximum: 10000; bei 0: 1000 ms)
	 * @param redGreenDur Die Dauer der Rot- und Grünphase in Millisekunden
	 * 			(Minimum: 1000, Maximum: 30000; bei 0: 5000 ms)
	 */
	Trafficlight(int pin_red, int pin_yellow, int pin_green, int msForSecond, int msForRedAndGreen);

	/**
	 * Schaltet auf rot, grün und dann wieder auf rot
	 */
	void stopGoStop();

	/**
	 * Animation, die die Lichter der Reihe nach anschaltet
	 */
	void animate();

	/**
	 * Lässt das gelbe Licht aufleuchten
	 */
	void flash();

	/**
	 * Übergibt den letzten Status
	 */
	int getTFStatus();

	/**
	 * Setze, ob die Phase fortgesetzt werden soll
	 */
	void setContinue(bool b);
	bool getContinue();

private:

	int redPin;
	int yellowPin;
	int greenPin;

	int thisSec;
	int redGreenDur;

	int next_tf_status;
	bool cont;
};

#endif
