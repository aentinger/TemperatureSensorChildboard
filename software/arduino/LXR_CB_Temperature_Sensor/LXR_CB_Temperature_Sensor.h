/**
 * @author Alexander Entinger, MSc / LXRobotics GmbH
 * @brief this library enables the user to communicate with the LXRobotics Childboard Temperature Sensor and provides functionality like reading the temperature, setting tmperature hysthere, etc. ...
 * @file LXR_CB_Temperature_Sensor.h
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef LXR_CB_TEMPERATURE_SENSOR_H_
#define LXR_CB_TEMPERATURE_SENSOR_H_

#include "Arduino.h"

#define SENSOR_DEFAULT_ADDRESS		(0x90>>1)

typedef void(*thermostat_event_callback_function)(void);

class LXR_CB_Temperature_Sensor {
public:
  /**
   * @brief Constructor
   * @param address i2c address of the sensor
   */
  LXR_CB_Temperature_Sensor(int const address);
  /**
   * @brief initializes the sensor
   */
  void begin();
  /**
   * @brief returns the temperature in degree celsius
   */
  int get_temperature();
  /**
   * @brief sets the temperature high and low register for thermostat control
   */
  void set_th(int const temp_high);
  void set_tl(int const temp_low);
  /**
   * @brief reads the temperature high and low for thermostat control
   */
  int get_th();
  int get_tl();
  /**
   * @brief attaches a callback function which is called in case of an thermostat event
   */
  void attach_thermostat_event_callback(thermostat_event_callback_function cb);
 
private:
  int m_address;
};

#endif

