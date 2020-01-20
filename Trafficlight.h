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
	 * Enum für den Status, den die Ampel gerade anzeigt
	 */
	typedef enum {
		RED = 0, RED_YELLLOW, GREEN, YELLOW
	}TF_Status;

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
	void stopGoStop(TF_Status startFrom);

	/**
	 * Animation, die die Lichter der Reihe nach anschaltet
	 */
	void animate();

	/**
	 * Lässt das gelbe Licht aufleuchten
	 */
	void flash();

	TF_Status getTFStatus();

private:

	int redPin;
	int yellowPin;
	int greenPin;

	int thisSec;
	int redGreenDur;

	TF_Status actual_tf_status;
};

#endif
