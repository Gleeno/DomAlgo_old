/* 
 * File:   Synapsis.hpp
 * Author: teo
 *
 * Created on December 12, 2015, 2:01 PM
 */

#ifndef SYNAPSIS_HPP
#define	SYNAPSIS_HPP
#include <iostream>
#include <libwebsockets.h>
#include <string>
#include "SynapsisBase.hpp"
#include <vector>
#include "Synapsis/sensor/Sensor.hpp"
#include "Synapsis/sensor/SimpleSwitch.hpp"
#include <unistd.h> //sleep

class Synapsis : public SynapsisBase {
private:
    std::string wsAddress;
    int wsPort;
    
public:   
    struct lws_context *context;
    static std::vector<Sensor*> sensors;
    
    Synapsis();
    int connect(std::string address="127.0.0.1", int port=9002);

    static int callback_instruction(
                         struct lws *wsi,
                         enum lws_callback_reasons reason, void *user,
                         void *in, size_t len);
    
    static lws_write_protocol parseInstruction(void ** in, Json::Value result,
    std::string* clientName, std::string* clientIp);
    static int notify(std::string message, Json::Value result);
    static int makeInstruction(std::string action, std::string* data,
            Json::Value result, sensType type= sensType::GENERIC,
            std::string id="no_id");
    static bool isSynapsisInstruction(Json::Value* instruction);
    static bool pairing(Json::Value instruction,Json::Value result,
            std::string* clientName, std::string* clientIp);
    static bool isPaired(std::string sensorId);
    static bool getDataSensor(Json::Value instruction, Json::Value result);
};
#endif	/* SYNAPSIS_HPP */