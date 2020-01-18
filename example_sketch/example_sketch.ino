#include <trafficlight.h>

// ENUM für Druckdauer
typedef enum {
  ignore = 0,
  short_press,
  long_press
} duration;

// ENUM für Modus
typedef enum {
  flashing = 0,
  runing
} tf_mode;

Trafficlight tf = Trafficlight(11, 9, 7, 1, 1);


void setup() {

}

void loop() {

}
