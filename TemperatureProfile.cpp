#include "TemperatureProfile.h"

/*
 * Sets a target temperature point at the specified time offset
 */
void TemperatureProfile::setTempAt(uint16_t secs,double temp)
{
  if (numTempPoints >= MAX_TEMP_POINTS) {
    // can't add any more temperature points
    return;
  }
  if (secs > duration) {
    duration = secs;
  }
  if (temp > maxTemp) {
    maxTemp = temp;
  }
  if (temp < minTemp) {
    minTemp = temp;
  }
  temperaturePoints[numTempPoints].offset = secs;
  temperaturePoints[numTempPoints].temperature = temp;
  numTempPoints++;
}

/*
 * Gets the interpolated target temperature point for the specified time
 */
double TemperatureProfile::getTempAt(uint16_t secs)
{
  if (secs > duration) {
    return temperaturePoints[numTempPoints-1].temperature;
  }
  for (int i=0;i<numTempPoints;i++) {
    if (temperaturePoints[i].offset == secs) {
      // exact time match, no interpolation needed
      return temperaturePoints[i].temperature;
    }
    else if (temperaturePoints[i].offset > secs) {
      // this temperature point is the one ahead of us; interpolate between last one and it
      double time_span = temperaturePoints[i].offset - temperaturePoints[i-1].offset;
      double temp_span = temperaturePoints[i].temperature - temperaturePoints[i-1].temperature;
      double interpolated = ((secs - temperaturePoints[i].offset)/time_span) * temp_span + temperaturePoints[i-1].temperature;
      return interpolated;
    }
  }
}

/*
 * returns the duration of the temperature profile, in seconds
 */
uint16_t TemperatureProfile::getDuration()
{
  return duration;
}

/*
 * returns the minimum temperature in the profile
 */
double TemperatureProfile::getMinTemp()
{
  return minTemp;
}

/*
 * returns the maximum temperature in the profile
 */
double TemperatureProfile::getMaxTemp()
{
  return maxTemp;
}

}

