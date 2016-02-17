/* 
 * File:   Synapsis.cpp
 * Author: teo
 * 
 * Created on December 12, 2015, 2:01 PM
 */

#include "Synapsis.hpp"
std::vector<Sensor*> Synapsis::sensors;
Synapsis::Synapsis() {
}

Synapsis::Synapsis(const Synapsis& orig) {
}

Synapsis::~Synapsis() {
}

int Synapsis::connect(std::string address, int port){
    this->wsAddress = address;
    this->wsPort=port;
    l("Server connection: address: " + address + ". Port: "+std::to_string(port));
    
    /* libwebsocket start */    
    struct lws_context_creation_info info;
    static struct lws_protocols protocols[] ={
        { "http-only", callback_http, 0 },
        { "instruction_protocol",callback_instruction, 0},
        {"streaming_protocol", callback_streaming, 0},
        { NULL, NULL, 0 }
    };
    memset(&info, 0, sizeof(info));
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
 int Synapsis::callback_http(
                         struct lws *wsi,
                         enum lws_callback_reasons reason, void *user,
                         void *in, size_t len)
{
  return 0;
}

 int Synapsis::callback_instruction(
                         struct lws *wsi,
                         enum lws_callback_reasons reason, void *user,
                         void *in, size_t len)
{
    int resultState = -10;
    int resultLen;
    unsigned char * data;
    int dataW;
    char name[settingsRaw["CLIENT_NAME_LENGHT"].asInt()];
    char ip[settingsRaw["IP_ADDRESS_LENGHT"].asInt()];
    //lws_get_peer_addresses(wsi,lws_get_socket_fd(wsi),
    //        name, sizeof(name),
    //        ip,sizeof(ip));
  switch (reason){   
    case LWS_CALLBACK_ESTABLISHED:
        std::cout << "Connected" << std::endl;
      break;
    case LWS_CALLBACK_RECEIVE:
      data = parseInstruction(&in, &resultState, &resultLen,(std::string) name,(std::string)ip); 
      if(resultState == 1) {
         dataW = lws_write(wsi, &data[LWS_SEND_BUFFER_PRE_PADDING],
                resultLen, LWS_WRITE_TEXT);  
         l( L_DATA_SENT);
      }
      else if(resultState == 2) {
        dataW = lws_write(wsi, &data[LWS_SEND_BUFFER_PRE_PADDING], 
                resultLen, LWS_WRITE_BINARY);  
        //lall("Data w " + dataW + ". RESULT: binary data");
      }
      else l((std::string)L_INVALID_INSTRUCTION );
      std::cout << "Result of parse instruction: " << resultState << std::endl;
      break;
     
    default:
      break;
    }
  return 0;
}
 int Synapsis::callback_streaming(
                         struct lws *wsi,
                         enum lws_callback_reasons reason, void *user,
                         void *in, size_t len)
{    
        
     return 0;
}
 
unsigned char* Synapsis::parseInstruction(void ** in, int* resultState,int* resultLen,
    std::string clientName, std::string clientIp) {
    std::string *a = (std::string*)in;
    std::cout << "Instr: size=" << a->length() << " and cont=" << *a <<  std::endl;
    Json::Value instruction;
    instruction = getJson('s',(std::string*)in);
    std::cout << "Raw inst.: " << instruction.toStyledString() << std::endl;
    unsigned char* result;
    std::vector<unsigned char> buf;
    std::string msg;
    msg.clear();
    
    if(isSynapsisInstruction(&instruction)) {
        sensType type = (sensType)instruction["type"].asInt();
        std::string action = instruction["action"].asString(); 
        if(action.compare(settingsRaw["A_PAIRING"].asString()) == 0) {
            if(!isPaired(instruction["id"].asString())) {
                if(type == sensType::TERMINAL) {
                    sensors.push_back(new Sensor(instruction["id"].asString(),
                            (sensType)instruction["type"].asInt(),
                            clientName, clientIp));
                    msg=L_SUCCESS;
                }
            }
            else
                msg=L_SENSOR_JUST_PAIRED;
            *resultState=settingsRaw["TEXT_FORMAT"].asInt();
        }
        else if(action.compare(settingsRaw["A_GET_DATA_SENSOR"].asString()) ==0) {
            if(isPaired(instruction["id"].asString())) {
                msg = "valOf1";
                std::cout << "label" << std::endl;
            }
            else
                msg=L_SENSOR_NOT_PAIRED;
            *resultState = settingsRaw["TEXT_FORMAT"].asInt();
        }
        else {
            *resultState =  settingsRaw["N_INSTRUCTION_NOT_DEFINED"].asInt();
            msg = L_INSTRUCTION_NOT_DEFINED;
        }
    }
    else *resultState = settingsRaw["N_BAD_INSTRUCTION"].asInt();
    if(*resultState == 2) *resultLen = buf.size();
    else *resultLen = msg.length();
    result = (unsigned char* ) malloc(*resultLen + LWS_SEND_BUFFER_PRE_PADDING);
    memset(result,0,*resultLen + LWS_SEND_BUFFER_PRE_PADDING);
    switch(*resultState) {
        case 1:
            memcpy(result+ LWS_SEND_BUFFER_PRE_PADDING,(unsigned char*)msg.c_str(), *resultLen); 
            break;
        case 2:
            std::cout << "Image size: " << *resultLen  << std::endl;
            memcpy(result+ LWS_SEND_BUFFER_PRE_PADDING,buf.data(), *resultLen);
            break;  
        default:
            memcpy(result+ LWS_SEND_BUFFER_PRE_PADDING,(unsigned char*)msg.c_str(), *resultLen); 
            break;
    } 
    return result;  
}

bool Synapsis::isSynapsisInstruction(Json::Value* instruction) {
    if( instruction->isNull() ||
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

 bool Synapsis::isPaired(std::string sensorId) {
        for(int i = 0; i< sensors.size();i++) {
            if (sensors[i]->getId().compare(sensorId) ==0)
                return true;
        }
        return false;
    }