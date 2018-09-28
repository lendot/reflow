#include "TemperatureProfile.h"

TemperatureProfile tempProfile;

void setup() {
  tempProfile.setTempAt(0,25);
  tempProfile.setTempAt(30,100);
  tempProfile.setTempAt(120,150);
  tempProfile.setTempAt(150,183);
  tempProfile.setTempAt(210,235);
  tempProfile.setTempAt(240,183);
}

void loop() {
  // put your main code here, to run repeatedly:

}
