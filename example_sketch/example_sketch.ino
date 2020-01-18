#include <Trafficlight.h>


// ENUM für Modus
typedef enum {
  FLASHING = 0,
  RUNNING
} trafficlfght_mode;

Trafficlight tf = Trafficlight(11, 9, 7, 1, 1);
unsigned long pushed, flashing_since;
boolean _remain = false;
trafficlfght_mode tf_mode;

void setup() {
  pinMode(5, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(2), push, RISING);
  attachInterrupt(digitalPinToInterrupt(2), unpush, FALLING);

  tf_mode = FLASHING;
  flashing_since = millis();

  tf.animate();
}

void loop() {
  switch (tf_mode) {
    case FLASHING:
      tf.flash();
      if (flashing_since > 20000) {
        _remain = !_remain;
        remain();
      }
      break;
    case RUNNING:
      tf.stopGoStop();
      break;
  }
}

void push() {
  pushed = millis();
}

void unpush() {
  unsigned long diff = millis() - pushed;
  if (diff < 30) {
    // nichts tun: Interrupt schnell beenden
  } else {
    switch (tf_mode) {

      case FLASHING:
        if (_remain) {
          _remain = !_remain;
        } else {
          tf_mode = RUNNING;
        }
        break;

      case RUNNING:
        if (diff <= 500) {
          _remain = !_remain;
          remain();
        } else {
          tf_mode = FLASHING;
          flashing_since = millis();
        }
        break;
    }
  }
}

void remain() {
  while (_remain) {

  }
}
