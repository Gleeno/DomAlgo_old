/* 
 * File:   Sensor.hpp
 * Author: teo
 *
 * Created on January 28, 2016, 4:03 PM
 */

#ifndef SENSOR_HPP
#define	SENSOR_HPP
#include <iostream>
enum sensType {
  SIMPLE_KNOB = 0,
  SIMPLE_SWITCH,
  ADV_KNOB_TUNER,
  ADV_SWITCH,
  SIMPLE_CAMERA,
  TERMINAL
};
class Sensor {
public:
    Sensor();
    Sensor(std::string, sensType);
    Sensor(const Sensor& orig);
    virtual ~Sensor();
private:
    std::string id;
    sensType type;
};

#endif	/* SENSOR_HPP */

