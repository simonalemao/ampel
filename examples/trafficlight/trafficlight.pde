#include <Trafficlight.h>

// ENUM für Modus
typedef enum {
  FLASHING = 0,
  RUNNING,
  SLEEP,
} trafficlfght_mode;

// Red pin = 8
// Yellow pin = 7
// Green pin = 6
// Sekunde als 0 ms (turns to 1000 ms automatically)
// Red/Green timeout: 0 ms (turns to 5000 ms automatically)
Trafficlight tf = Trafficlight(8, 7, 6, 0, 0);

unsigned long pushed, flashing_since;
boolean _remain = false;
trafficlfght_mode tf_mode;

// Beide pins an denselben Taster angeschlossen
const byte pushPin = 2;
const byte unpushPin = 3;

int lastTFStatus;

void setup() {
  pinMode(pushPin, INPUT_PULLUP);
  pinMode(unpushPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pushPin), push, FALLING);
  attachInterrupt(digitalPinToInterrupt(unpushPin), unpush, RISING);

  tf_mode = FLASHING;
  flashing_since = millis();

  tf.animate();
}

void loop() {
  switch (tf_mode) {

    case FLASHING:
      tf.flash();
      if ((millis() - flashing_since) > 20000) {
        tf_mode = SLEEP;
      }
      break;

    case RUNNING:
      tf.stopGoStop();
      break;

    case SLEEP:
      break;
  }
}

void push() {
  pushed = millis();
}

void unpush() {
  unsigned long diff = millis() - pushed;
  if (diff < 50) {
    // nichts tun: Interrupt schnell beenden
  } else {
    switch (tf_mode) {

      case FLASHING:
        tf_mode = RUNNING;
        break;

      case RUNNING:
        if (!tf.getContinue()) {
          tf.setContinue(true);
        } else if (diff <= 700) {
          // Zustand beibehalten
          tf.setContinue(false);
        } else {
          // Zurück zu FLASHING
          tf_mode = FLASHING;
          flashing_since = millis();
        }
        break;

      case SLEEP:
        tf_mode = FLASHING;
        flashing_since = millis();
        break;
    }
  }
}
