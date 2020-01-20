#include <Trafficlight.h>


// ENUM für Modus
typedef enum {
  FLASHING = 0,
  RUNNING,
  SLEEP,
  HOLD
} trafficlfght_mode;

Trafficlight tf = Trafficlight(8, 7, 6, 1, 1);
unsigned long pushed, flashing_since;
boolean _remain = false;
trafficlfght_mode tf_mode;
const byte pushPin = 2;
const byte unpushPin = 3;

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
      }
      break;
    case RUNNING:
      Serial.println("running");
      tf.stopGoStop(RED);
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
    Serial.println("too short");
  } else {
    switch (tf_mode) {

      case FLASHING:
        tf_mode = RUNNING;
        break;

      case RUNNING:
        if (diff <= 500) {
          Serial.println("short press");
          // Zusand beibehalten
        } else {
          Serial.println("long press");
          tf_mode = FLASHING;
          flashing_since = millis() + 5000;
        }
        break;

      case SLEEP:
        tf_mode = FLASHING;
        flashing_since = millis();
        break;
    }
  }
}
