/**
 * @author Alexander Entinger, MSc / LXRobotics GmbH
 * @brief this sketch demonstrates how to read the temperature of the LXRobotics Childboard Temperature Sensor using the LXR_Childboard_Temperature_Sensor Library
 * @file read_temperature_serial.ino
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include "LXR_CB_Temperature_Sensor.h"
#include <Wire.h> // dont forget this

// instantiate sensor
LXR_CB_Temperature_Sensor temp_sensor(SENSOR_DEFAULT_ADDRESS);

void setup() {
  // dont forget to call this first
  Wire.begin();
  // initialize sensor
  temp_sensor.begin();
  // initialize serial interface  
  Serial.begin(115200);
}

void loop() {
  int const temperature = temp_sensor.get_temperature();
  if(temperature != -128) {
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" C");
  } else {
   Serial.println("Error, could not read temperature"); 
  }
  delay(1000); 
}
