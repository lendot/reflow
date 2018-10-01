#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include "TemperatureProfile.h"

#define OLED_CS 9
#define OLED_DC 5
#define OLED_RST 6
Adafruit_SSD1351 display = Adafruit_SSD1351(OLED_CS, OLED_DC, OLED_RST);

TemperatureProfile tempProfile;

void setup() {
  Serial.begin(115200);
  Serial.print("Reflow");
  display.begin();

  Serial.println("init");

  tempProfile.setTempAt(0,25);
  tempProfile.setTempAt(30,100);
  tempProfile.setTempAt(120,150);
  tempProfile.setTempAt(150,183);
  tempProfile.setTempAt(210,235);
  tempProfile.setTempAt(240,183);
  Serial.println("done");
}

void loop() {
  // put your main code here, to run repeatedly:

}
