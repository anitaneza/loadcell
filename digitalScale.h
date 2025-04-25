#ifndef DIGITALSCALE_H
#define DIGITALSCALE_H

#include <HX711.h>
#include "wifiManager.h"

class digitalScale {
private:
  HX711 scale;
  float calfact;

public:
  digitalScale(int dout, int sck, float calibration_factor);
  void begin();
  void resetScale();
  float readScale();
};

#endif
