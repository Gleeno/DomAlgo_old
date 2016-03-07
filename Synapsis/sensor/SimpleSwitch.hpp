/* 
 * File:   SimpleSwitch.hpp
 * Author: teo
 *
 * Created on February 23, 2016, 2:57 PM
 */

#ifndef SIMPLESWITCH_HPP
#define	SIMPLESWITCH_HPP

class SimpleSwitch : public Sensor {
public:
    SimpleSwitch(std::string id, sensType type, std::string name, std::string ip);
    Json::Value getDataSensor();
    bool getState();
    int getSwitchState();
    
private:
    bool switchState = false;
};

#endif	/* SIMPLESWITCH_HPP */

