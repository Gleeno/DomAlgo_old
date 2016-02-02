/* 
 * File:   Sensor.hpp
 * Author: teo
 *
 * Created on January 28, 2016, 4:03 PM
 */

#ifndef SENSOR_HPP
#define	SENSOR_HPP
#include <iostream>
#include <json/value.h>
enum sensType {
  SIMPLE_KNOB = 0,
  SIMPLE_SWITCH,
  ADV_KNOB_TUNER,
  ADV_SWITCH,
  SIMPLE_CAMERA, //INPUT
  TERMINAL  //OUTPUT
};
class Sensor {
public:
    Sensor();
    Sensor(std::string, sensType, std::string name, std::string ip);
    virtual ~Sensor();
    sensType getType();
    std::string getId();
    int getVal();
private:
    std::string id;
    sensType type;
    std::string name;
    std::string ip;
    int value;
};

#endif	/* SENSOR_HPP */

