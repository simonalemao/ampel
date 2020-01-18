# Ampel // Projekt: Eingebettete Software

Eine Bibliothek um eine Ampel zu simluieren.

Um ein Prellen des Tasters auszuschließen werden nur Signale über 10ms weiterverarbeitet.
> https://de.wikipedia.org/wiki/Prellen

Sekunden werden im Konstruktor definiert. Das gilt nicht für die Zeit nach der die Ampel in den Schlafmodus gehen soll.

Die Länge der Rot- und der Grünphase werden im Konstruktor definiert.

Eine Ampelphase besteht aus:
rot (x Sekunden)
rot-geld (2 Sekunden)
grün (x Sekunden)
gelb (3 Sekunden)
rot (x Sekunden)

