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
// Second defined as 0 ms (turns to 1000 ms automatically)
// Red/Green timeout set to 0 ms (turns to 5000 ms automatically)
Trafficlight tf = Trafficlight(8, 7, 6, 0, 0);

unsigned long pushed, flashing_since;
boolean _remain = false;
trafficlfght_mode tf_mode;

// Both pins connected to same Button
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

  Serial.begin(9600);
  delay(1000);
  Serial.println("animate");
  tf.animate();
}

void loop() {
  switch (tf_mode) {

    case FLASHING:
      Serial.println("flashing");
      tf.flash();
      if ((millis() - flashing_since) > 20000) {
        tf_mode = SLEEP;
        Serial.println("sleep");
      }
      break;

    case RUNNING:
      Serial.println("running");
      tf.stopGoStop();
      break;

    case SLEEP:
      break;
  }
}

void push() {
  pushed = millis();
  Serial.println("push");
}

void unpush() {
  Serial.println("unpush");
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
          Serial.println("continue");
        } else if (diff <= 700) {
          Serial.println("short press");
          // Zusand beibehalten
          tf.setContinue(false);
          Serial.println("dont continue");
        } else {
          Serial.println("long press");
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
