/* 
 * File:   Synapsis.cpp
 * Author: teo
 * 
 * Created on December 12, 2015, 2:01 PM
 */

#include "Synapsis.hpp"
std::vector<Sensor*> Synapsis::sensors;

Synapsis::Synapsis(){}

int Synapsis::connect(std::string address, int port) {
    this->wsAddress = address;
    this->wsPort = port;
    l("Server connection: address: " + address + ". Port: " + std::to_string(port));

    /* libwebsocket start */
    struct lws_context_creation_info info;
    static struct lws_protocols protocols[] = {
        { "instruction_protocol", callback_instruction, 0},
        { NULL, NULL, 0}
    };
    memset(&info, 0, sizeof (info));
    info.port = this->wsPort;
    info.iface = NULL;
    info.protocols = protocols;
    info.extensions = lws_get_internal_extensions();
    info.ssl_cert_filepath = NULL;
    info.ssl_private_key_filepath = NULL;
    info.gid = -1;
    info.uid = -1;
    info.options = 0;
    this->context = lws_create_context(&info);
    if (this->context == NULL) {
        fprintf(stderr, "libwebsocket init failed\n");
        //return -1;
    }
    return 0;
}

//callbacks

int Synapsis::callback_instruction(
        struct lws *wsi,
        enum lws_callback_reasons reason, void *user,
        void *in, size_t len) {
    int dataW;
    lws_write_protocol writeProtocol;
    Json::Value result;
    std::string name = "anme";
    std::string ip = "2344";
    
    switch (reason) {
    case LWS_CALLBACK_ESTABLISHED:
        l((std::string)L_CONNECTED);
        break;
    case LWS_CALLBACK_RECEIVE:
        writeProtocol = parseInstruction(&in, &result, &name, &ip);
        if (writeProtocol == LWS_WRITE_TEXT || writeProtocol == LWS_WRITE_BINARY) {
            dataW = lws_write(wsi, (unsigned char*)result.asString().data(), result.asString().length(), writeProtocol);
            l(std::to_string(dataW) + " DATA SENT: " + result.asString());
        }
        else l((std::string)L_INVALID_INSTRUCTION);
    break;
    }
    return 0;
}

lws_write_protocol Synapsis::parseInstruction(void ** in, Json::Value result,
        std::string* clientName, std::string* clientIp) {
    Json::Value instruction;
    std::string action;
    try {
        instruction = getJson('s', (std::string*)in);
    }
    catch (int e) { std::cout << "Json parse error: errno: " << e << std::endl; }
    action = instruction["action"].asString();
    if (isSynapsisInstruction(&instruction)) {
        //action PAIRING
        if(action.compare(settingsRaw["A_PAIRING"].asString()) == 0)
            pairing(instruction,result, clientName, clientIp);
        //action get data sensor
        else if(action.compare(settingsRaw["A_GET_DATA_SENSOR"].asString()) == 0)
            getDataSensor(instruction,result);
        //action not defined
        else
            notify(L_INSTRUCTION_NOT_DEFINED + action ,&result);
        return LWS_WRITE_TEXT;        
    }
    //notify(settingsRaw["L_INVALID_INSTRUCTION"].asString(),result);
    return (lws_write_protocol)settingsRaw["N_BAD_INSTRUCTION"].isInt();
}
/*
    if (isSynapsisInstruction(&instruction)) {
        sensType type = (sensType) instruction["type"].asInt();
        std::string action = instruction["action"].asString();
        if (action.compare(settingsRaw["A_PAIRING"].asString()) == 0) {
            if (!isPaired(instruction["id"].asString())) {
                if (type == sensType::TERMINAL) {
                    sensors.push_back(new Sensor(instruction["id"].asString(),
                            (sensType) instruction["type"].asInt(),
                            clientName, clientIp));
                    msg = L_SUCCESS;
                }
                else {
                    msg= L_SENSOR_TYPE_UNKNOWN;
                }
            }    
            else
                msg = L_SENSOR_JUST_PAIRED;            
            *resultState = settingsRaw["TEXT_FORMAT"].asInt();
        } 
        else if (action.compare(settingsRaw["A_GET_DATA_SENSOR"].asString()) == 0) {
            if (isPaired(instruction["id"].asString())) {
                *resultState = settingsRaw["TEXT_FORMAT"].asInt();
                msg = "valOf1";
            } else
                msg = L_SENSOR_NOT_PAIRED;
            *resultState = settingsRaw["TEXT_FORMAT"].asInt();
        } 
        else {
            *resultState = settingsRaw["N_INSTRUCTION_NOT_DEFINED"].asInt();
            msg = L_INSTRUCTION_NOT_DEFINED;
        }
    } 
    else *resultState = settingsRaw["N_BAD_INSTRUCTION"].asInt();
    //
    if (*resultState == 2) *resultLen = buf.size();
    else *resultLen = msg.length();
    result = (unsigned char*) malloc(*resultLen + LWS_SEND_BUFFER_PRE_PADDING * sizeof(unsigned char));
    memset(result, 0, *resultLen + LWS_SEND_BUFFER_PRE_PADDING);
    switch (*resultState) {
    case 1:
        std::cout << "Text size: " << *resultLen << std::endl;
        memcpy(result + LWS_SEND_BUFFER_PRE_PADDING, (unsigned char*) msg.c_str(), *resultLen);
        break;
    case 2:
        std::cout << "Binary size: " << *resultLen << std::endl;
        memcpy(result + LWS_SEND_BUFFER_PRE_PADDING, buf.data(), *resultLen);
        break;
    default:
        std::cout << "[NO_FORMAT] size: " << *resultLen << std::endl;
        memcpy(result + LWS_SEND_BUFFER_PRE_PADDING, (unsigned char*) msg.c_str(), *resultLen);
        break;
    }
    return result;
}
*/

bool Synapsis::isSynapsisInstruction(Json::Value* instruction)
{
    if (instruction->isNull() ||
            instruction->empty() ||
            (!instruction->isMember("action")) ||
            (!instruction->isMember("data")) ||
            (!instruction->isMember("id")) ||
            (!instruction->isMember("type"))
            ) {
        l(L_WRONG_INSTRUCTION_FORMAT);
        return false;
    }
    l(L_RIGHT_INSTRUCTION_FORMAT);
    return true;
}

bool Synapsis::isPaired(std::string sensorId)
{
    for (int i = 0; i < sensors.size(); i++) {
        if (sensors[i]->getId().compare(sensorId) == 0)
            return true;
    }
    return false;
}

int Synapsis::notify(std::string message, Json::Value result) {
    makeInstruction(settingsRaw["A_NOTIFY"].asString(),&message,result);
    return settingsRaw["N_SUCCESS"].asInt();
}

bool Synapsis::pairing(Json::Value instruction, Json::Value result,
        std::string* clientName, std::string* clientIp) {
    std::string id= instruction["id"].asString();
    sensType type = (sensType) instruction["type"].asInt();
    if (!isPaired(id)) {
                if (type == sensType::TERMINAL) {
                    sensors.push_back(new Sensor(id,type,*clientName, *clientIp));
                    notify(L_SENSOR_PAIRED_SUCCESS,&result);
                }
                else if (type == sensType::SIMPLE_SWITCH) {
                    sensors.push_back(new SimpleSwitch(id,type,*clientName, *clientIp));
                    notify(L_SENSOR_PAIRED_SUCCESS,&result);
                }
                else
                    notify(L_SENSOR_TYPE_UNKNOWN,&result);
            }    
    else
        notify(L_SENSOR_JUST_PAIRED,&result);
    return true;
}

bool Synapsis::getDataSensor(Json::Value instruction, Json::Value result) {
    std::string action = instruction["action"].asString();
    std::string id= instruction["id"].asString();
    sensType type = (sensType)instruction["type"].asInt();
    std::string data;
    Json::Value tmp;
    
    if(sensors.size() <= 0 ) {
        notify(L_NO_SENSORS,result);
        return false;
    }
    if(id.compare("all") == 0) {
        for(int i=0; i <sensors.size();i++) {           
            tmp["action"] = settingsRaw["A_GET_DATA_SENSOR"].asString();
            tmp["id"] = sensors[i]->getId();
            tmp["type"] = std::to_string(sensors[i]->getType());
            tmp["data"]["test"]= "";//.append(sensors[i]->getDataSensor());
        }
        makeInstruction(action,&data,result,type,id);
    }
    return true;
}

int Synapsis::makeInstruction(std::string action, std::string* data, Json::Value result, sensType type, std::string id) {
    result["action"] = action;
    result["id"] = id;
    result["type"] = std::to_string((int)type);
    result["data"] = data;
    return settingsRaw["N_SUCCESS"].asInt();
}