/**
 * @author Alexander Entinger, MSc / LXRobotics GmbH
 * @brief this sketch demonstrates how use the thermostat function of the LXRobotics Childboard Temperature Sensor using the LXR_Childboard_Temperature_Sensor Library
 * @file thermostat.ino
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include "LXR_CB_Temperature_Sensor.h"
#include <Wire.h> // dont forget this

// instantiate sensor
LXR_CB_Temperature_Sensor temp_sensor(SENSOR_DEFAULT_ADDRESS);

int const temp_low = 29; 
int const temp_high = 30;

void setup() {
  // dont forget to call this first
  Wire.begin();
  // initialize sensor
  temp_sensor.begin();
  // initialize serial interface  
  Serial.begin(115200);
  // set temperature
  temp_sensor.set_tl(temp_low);
  temp_sensor.set_th(temp_high);
  // read temperature
  Serial.print("TL = ");
  Serial.print(temp_sensor.get_tl());
  Serial.println(" C");
  Serial.print("TH = ");
  Serial.print(temp_sensor.get_th());
  Serial.println(" C");
  // attach callback in case of thermostat events
  temp_sensor.attach_thermostat_event_callback(&thermostat_event);
}

static boolean thermostat_event_occured = false;
/**
 * this function is called in case of an thermostat event, runs in isr context
 */
void thermostat_event() {
  thermostat_event_occured = true;
}

void loop() {
  if(thermostat_event_occured) {
    thermostat_event_occured = false;
    Serial.print("Thermostat Event occured: ");
    if(temp_sensor.get_temperature() >= temp_high) Serial.println(" Temp >= TH");
    else if(temp_sensor.get_temperature() <= temp_low) Serial.println(" Temp <= TH");
  }
  // display current temperature
  Serial.print("Current Temperature = ");
  Serial.print(temp_sensor.get_temperature());
  Serial.println(" C");
  delay(2000);
}
