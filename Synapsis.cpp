/* 
 * File:   Synapsis.cpp
 * Author: teo
 * 
 * Created on December 12, 2015, 2:01 PM
 */

#include "Synapsis.hpp"
std::vector<Sensor> Synapsis::sensors;
Synapsis::Synapsis() {
}

Synapsis::Synapsis(const Synapsis& orig) {
}

Synapsis::~Synapsis() {
}

int Synapsis::connect(std::string address, int port){
    this->wsAddress = address;
    this->wsPort=port;
    l("start connect: address=" + address + " and port="+std::to_string(port));
    
    /* libwebsocket start */    
    struct lws_context_creation_info info;
    static struct lws_protocols protocols[] ={
        { "http-only", callback_http, 0 },
        { "instruction_protocol",callback_instruction, 0, 200000 },
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
  switch (reason){    
    case LWS_CALLBACK_ESTABLISHED:
      l(L_CONNECTED);
      break;
    case LWS_CALLBACK_RECEIVE:
      data = parseInstruction(&in, &resultState, &resultLen);  
      if(resultState == 1) {
         dataW = lws_write(wsi, &data[LWS_SEND_BUFFER_PRE_PADDING], resultLen, LWS_WRITE_TEXT);  
         lall( L_DATA_SENT  +  dataW );
      }
      else if(resultState == 2) {
        dataW = lws_write(wsi, &data[LWS_SEND_BUFFER_PRE_PADDING], resultLen, LWS_WRITE_BINARY);  
        //lall("Data w " + dataW + ". RESULT: binary data");
      }
      else lall(L_INVALID_INSTRUCTION + resultState);
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
 
unsigned char* Synapsis::parseInstruction(void ** in, int* resultState,int* resultLen) {
    Json::Value instruction;
    instruction = getJson('s',(std::string*)in);
    std::string action = instruction["action"].asString();    
    if(action.compare("connect") == 0) {
        if(instruction["data"]["type"] == sensType::TERMINAL)
            Synapsis::sensors.push_back(Sensor("a", sensType::TERMINAL));
        l("Sensor: TERMINAL");
    }
    
    return NULL; 
}
