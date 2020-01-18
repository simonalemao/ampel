# Ampel // Projekt: Eingebettete Software

Eine Bibliothek um eine Ampel zu simluieren.

Um ein Prellen des Tasters auszuschließen werden nur Signale über 30ms weiterverarbeitet.
https://de.wikipedia.org/wiki/Prellen
Ein kurzes Drücken des Tasters darf höchstens 500 ms dauern
Ein langes Drücken des Tasters muss mindestens 501 ms dauern

Sekunden werden im Konstruktor definiert. Das gilt nicht für die Zeit nach der die Ampel in den Schlafmodus gehen soll.

Die Länge der Rot- und der Grünphase werden im Konstruktor definiert.

Eine Ampelphase besteht aus:
rot (x Sekunden)
rot-geld (2 Sekunden)
grün (x Sekunden)
gelb (3 Sekunden)
rot (x Sekunden)

Der Beispielsketch nutzt Interrupts. Dafür wird ein Arduini benötigt, der Interrupts verarbeiten kann. Weiterhin muss der Taster ann einen Pin angeschlossen sein, der für Interrupts geeignet ist.
https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
Der Beispielsketch ist für einen Arduino Nano ausgelegt und der Pin für den Taster muss 2 oder 3 sein.
