# Ampel // Projekt: Eingebettete Software

Eine Bibliothek um eine Ampel zu simluieren.

## Konstruktor
```
Trafficlight(int pin_red, int pin_yellow, int pin_green, int msForSecond, int msForRedAndGreen);
```
* pin_red: Pin, der das rote Licht symbolisiert
* pin_yellow: Pin, der das gelbe Licht symbolisiert
* pin_red: Pin, der das grüne Licht symbolisiert

Sekunden werden im Konstruktor definiert.

## Funktionen

```
void stopGoStop()
```
Lässt die Ampel eine Phase durchlaufen. Wenn per setContinue(bool) gesetzt wurde, dass die Ampel nicht weiterlaufen soll, bleibt sie stehen.

Die Länge der Rot- und der Grünphase werden im Konstruktor definiert.

Eine Ampelphase besteht aus:
* rot (x Sekunden)
* rot-geld (2 Sekunden)
* grün (x Sekunden)
* gelb (3 Sekunden)
* rot (x Sekunden)

```
void animate()
```
Startet eine Animation

```
void flash()
```
Lässt das gelbe Licht einmal aufblinken

```
void setContinue(bool b);
bool getContinue();
```
Stellt ein, ob die Ampel weiterlaufen soll oder nicht.

## Sonstiges


Um ein Prellen des Tasters auszuschließen werden nur Signale über 50 ms weiterverarbeitet. ([https://de.wikipedia.org/wiki/Prellen](https://de.wikipedia.org/wiki/Prellen))

Ein kurzes Drücken des Tasters darf höchstens 700 ms dauern
Ein langes Drücken des Tasters muss mindestens 701 ms dauern.

Der Beispielsketch nutzt Interrupts. Dafür wird ein Arduino Nano benötigt, welcher Interrupts verarbeiten kann. Weiterhin muss der Taster an den Pins 2 und 3 angeschlossen sein, da nur diese für Interrupts geeignet sind.
https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
Der Beispielsketch ist für einen Arduino Nano ausgelegt und der Pin für den Taster muss 2 oder 3 sein.
