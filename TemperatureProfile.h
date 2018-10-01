#ifndef __TemperatureProfile_h
#define __TemperatureProfile_h

#include <Arduino.h>

#define MAX_TEMP_POINTS 10

typedef struct {
  uint16_t offset;
  double temperature;
} temperature_point_t;

class TemperatureProfile {
  public:
    void setTempAt(uint16_t secs,double temp);
    double getTempAt(uint16_t sec);
    uint16_t getDuration();
    double getMinTemp();
    double getMaxTemp();
    
  private:
    uint16_t duration=0;
    uint16_t numTempPoints=0;
    double minTemp = 10000;
    double maxTemp = -1;
    temperature_point_t temperaturePoints[MAX_TEMP_POINTS];
};

#endif // __TemperatureProfile_h

