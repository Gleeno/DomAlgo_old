/* 
 * File:   SimpleSwitch.cpp
 * Author: teo
 * 
 * Created on February 23, 2016, 2:57 PM
 */

#include "SimpleSwitch.hpp"

SimpleSwitch::SimpleSwitch(std::string id, sensType type, std::string name, std::string ip) 
: Sensor(id,type,name,ip)
{
}

bool SimpleSwitch::getState() {
    return this->switchState;
}
int SimpleSwitch::getSwitchState(){
    return this->switchState;
}
Json::Value SimpleSwitch::getDataSensor() {
    Json::Value data;
    data["sensor"] = Sensor::getDataSensor();
    data["sensor"]["spec"]["switchState"] =  std::to_string(getSwitchState());
    return data;
}

