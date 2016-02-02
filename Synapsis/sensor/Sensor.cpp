/* 
 * File:   Sensor.cpp
 * Author: teo
 * 
 * Created on January 28, 2016, 4:03 PM
 */

#include "Sensor.hpp"

Sensor::Sensor(std::string id, sensType type, std::string name, std::string ip) {
    this->id = id;
    this->type = type;
    this->name = name;
    this->ip = ip;
}

Sensor::Sensor() {
    
}
Sensor::~Sensor() {
}

sensType Sensor::getType() {
    return this->type;
}
std::string Sensor::getId() {
    return this->id;
}

int Sensor::getVal() {
    return this->value;
}

