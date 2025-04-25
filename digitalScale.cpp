#include "digitalScale.h"
#include "wifiManager.h"
#include "configuration.h"

digitalScale::digitalScale(int dout, int sck, float calibration_factor)
  : scale(), calfact(calibration_factor) {
  scale.begin(dout, sck);
}

void digitalScale::begin() {
  scale.set_scale(calibration_factor);
}

void digitalScale::resetScale() {
  Serial.println("Resetting scale...");
  scale.tare();
}

float digitalScale::readScale() {
  float berat = round(scale.get_units(10))+163;
//  Serial.println(round(1.7));
  return berat;
}
