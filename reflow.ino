#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include "TemperatureProfile.h"

#define OLED_CS 9
#define OLED_DC 5
#define OLED_RST 6
Adafruit_SSD1351 display = Adafruit_SSD1351(OLED_CS, OLED_DC, OLED_RST);

long start_time=0;
uint16_t duration;
double pxtime;
double minTemp,maxTemp;
uint16_t prev_temp_y = 0;
int16_t last_pxtime = -1;

TemperatureProfile tempProfile;

#define NUM_TEMP_READINGS 5
double temp_buffer[NUM_TEMP_READINGS];
uint8_t temp_idx=0;

void setup() {
  Serial.begin(115200);
  delay(2000);
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

  for (int i=0;i<NUM_TEMP_READINGS;i++) {
    temp_buffer[i]=0.0;
  }

  duration = tempProfile.getDuration();
  display.fillScreen(0x0000);
  minTemp = tempProfile.getMinTemp();
  maxTemp = tempProfile.getMaxTemp();
  pxtime = duration/128.0;
  for (uint16_t x=0;x<128;x++) {
    uint16_t t = (uint16_t)(x * pxtime);
    double temp = tempProfile.getTempAt(t);
    Serial.print("t: "); Serial.print(t);
    Serial.print(" temp: "); Serial.println(temp);
    double normalized_temp = (temp - minTemp) / (maxTemp - minTemp);
    uint16_t temp_y = (uint16_t)round((normalized_temp * 64));
    if (temp_y==64) {
      temp_y--;
    }
    temp_y = 127 - temp_y;
    display.drawPixel(x,temp_y,0xffff);
  }
  start_time = millis();
}

double get_average_temp(double new_temp)
{
  temp_buffer[temp_idx]=new_temp;
  temp_idx++;
  if (temp_idx>=NUM_TEMP_READINGS) {
    temp_idx=0;
  }
  double acc=0;
  for (int i=0;i<NUM_TEMP_READINGS;i++) {
    acc+=temp_buffer[temp_idx];
  }
  return acc/NUM_TEMP_READINGS;
}

void update_display()
{
  display.setCursor(0,0);
  display.setTextColor(0xffff,0x0000);
  display.setTextSize(2);
  long run_time = (millis() - start_time)/1000;
  if (run_time > duration) {
    display.println("Time --   ");
    display.println("Trgt --   ");
    return;
  }
  display.print("Time "); display.print(run_time); display.println("s");
  double temp_target = tempProfile.getTempAt(run_time);
  display.print("Trgt "); display.print((int)round(temp_target));display.println(" C");
  double temp = get_average_temp(random (temp_target-10,temp_target+10));
  display.print("Temp "); display.print((int)round(temp));display.println(" C");

  uint16_t x = run_time / pxtime;
  if (x!=last_pxtime) {
    double normalized_temp = (temp - minTemp) / (maxTemp - minTemp);
    uint16_t temp_y = (uint16_t)round((normalized_temp * 64));
    if (temp_y==64) {
      temp_y--;
    }
    temp_y = 127 - temp_y;
    if (x>0) {
      display.drawLine(x-1,prev_temp_y,x,temp_y,0xf800); 
    } else {
      display.drawPixel(x,temp_y,0xf800);
    }
    last_pxtime=x;
    prev_temp_y = temp_y;
  }
}

void loop() {
  update_display();
  delay(10);
}
