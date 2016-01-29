/* 
 * File:   Sensor.cpp
 * Author: teo
 * 
 * Created on January 28, 2016, 4:03 PM
 */

#include "Sensor.hpp"

Sensor::Sensor(std::string id, sensType type) {
    this->id = id;
    this->type = type;
}

Sensor::Sensor(const Sensor& orig) {
}

Sensor::~Sensor() {
}

