/**
 * @author Alexander Entinger, MSc / LXRobotics GmbH
 * @brief this library enables the user to communicate with the LXRobotics Childboard Temperature Sensor and provides functionality like reading the temperature, setting tmperature hysthere, etc. ...
 * @file LXR_CB_Temperature_Sensor.cpp
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include "LXR_CB_Temperature_Sensor.h"
#include "Wire.h"

#define READ_TEMPERATURE		(0xAA)
#define START_CONVERSION		(0xEE)
#define STOP_CONVERSION			(0x22)
#define ACCESS_TH			(0xA1)
#define ACCESS_TL			(0xA2)
#define ACCESS_CONFIG			(0xAC)

/**
 * @brief Constructor
 * @param address i2c address of the sensor
 */
LXR_CB_Temperature_Sensor::LXR_CB_Temperature_Sensor(int const address) : 
m_address(address) {

}

/**
 * @brief initializes the sensor
 */
void LXR_CB_Temperature_Sensor::begin() {
  // configure i2c sensor to measure temperature continously
  Wire.beginTransmission(m_address);
  Wire.write(ACCESS_CONFIG);
  Wire.write(0x00); // clear all flags
  Wire.endTransmission();
  delay(1);
  // start conversion
  Wire.beginTransmission(m_address);
  Wire.write(START_CONVERSION);
  Wire.endTransmission();
  delay(1);
}

/**
 * @brief returns the temperature
 */
int LXR_CB_Temperature_Sensor::get_temperature() {
  // read temperaure from sensor
  Wire.beginTransmission(m_address);
  Wire.write(READ_TEMPERATURE);
  Wire.endTransmission();
  Wire.requestFrom(m_address, 2);
  delay(1);
  if(Wire.available() == 2) {
    int8_t const temp_high_byte = Wire.read();
    Wire.read(); // we dont use the 0.5 degrees here
    return temp_high_byte;
  }
  return -128;
}

/**
 * @brief sets the temperature high and low register for thermostat control
 */
void LXR_CB_Temperature_Sensor::set_th(int const temp_high) {
  Wire.beginTransmission(m_address);
  Wire.write(ACCESS_TH);
  Wire.write(temp_high);
  Wire.write(0x00);
  Wire.endTransmission();
}
void LXR_CB_Temperature_Sensor::set_tl(int const temp_low) {
  Wire.beginTransmission(m_address);
  Wire.write(ACCESS_TL);
  Wire.write(temp_low);
  Wire.write(0x00);
  Wire.endTransmission();  
}
 
/**
 * @brief reads the temperature high and low for thermostat control
 */
int LXR_CB_Temperature_Sensor::get_th() {
  Wire.beginTransmission(m_address);
  Wire.write(ACCESS_TH);
  Wire.endTransmission();
  Wire.requestFrom(m_address, 2);
  delay(1);
  if(Wire.available() == 2) {
    int8_t const th_high = Wire.read();
    Wire.read(); // we dont use the 0.5 degree here
    return th_high;
  }
  return -128;
}
int LXR_CB_Temperature_Sensor::get_tl() {
  Wire.beginTransmission(m_address);
  Wire.write(ACCESS_TL);
  Wire.endTransmission();
  Wire.requestFrom(m_address, 2);
  delay(1);
  if(Wire.available() == 2) {
    int8_t const tl_high = Wire.read();
    Wire.read(); // we dont use the 0.5 degree here
    return tl_high;
  }
  return -128; 
}

/**
 * @brief attaches a callback function which is called in case of an thermostat event
 */
void LXR_CB_Temperature_Sensor::attach_thermostat_event_callback(thermostat_event_callback_function cb) {
  if(cb != 0) attachInterrupt(1, cb, CHANGE);  
}
