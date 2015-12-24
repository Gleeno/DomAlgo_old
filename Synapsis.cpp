/* 
 * File:   Synapsis.cpp
 * Author: teo
 * 
 * Created on December 12, 2015, 2:01 PM
 */

#include "Synapsis.hpp"

Synapsis::Synapsis() {
    wsAddress = getSettingsRaw()["WS_ADDRESS"].asString();
    wsPort = getSettingsRaw()["WS_PORT"].asInt();
}

Synapsis::Synapsis(const Synapsis& orig) {
}

Synapsis::~Synapsis() {
}

int Synapsis::connect(std::string address, int port){
    l("start connect: address=" + address + " and port="+std::to_string(port));
    /* libwebsocket start */
    
    struct lws_context_creation_info info;
    static struct libwebsocket_protocols protocols[] ={
        { "http-only", callback_http, 0 },
        { "instruction_protocol",callback_instruction, 0, 200000 },
        {"streaming_protocol", callback_streaming, 0},
        { NULL, NULL, 0 }
    };
    memset(&info, 0, sizeof(info));
    info.port = this->wsPort;
    info.iface = NULL;
    info.protocols = protocols;
    info.extensions = libwebsocket_get_internal_extensions();
    info.ssl_cert_filepath = NULL;
    info.ssl_private_key_filepath = NULL;
    info.gid = -1;
    info.uid = -1;
    info.options = 0;
    this->context = libwebsocket_create_context(&info);
    if (this->context == NULL) {
    fprintf(stderr, "libwebsocket init failed\n");
    //return -1;
    }
    return 0;
}

//callbacks
 int Synapsis::callback_http(struct libwebsocket_context *context,
                         struct libwebsocket *wsi,
                         enum libwebsocket_callback_reasons reason, void *user,
                         void *in, size_t len)
{
  return 0;
}

 int Synapsis::callback_instruction(struct libwebsocket_context *context,
                         struct libwebsocket *wsi,
                         enum libwebsocket_callback_reasons reason, void *user,
                         void *in, size_t len)
{
  int resultState;
  int resultLen;
  unsigned char * data;
  int dataW;
  switch (reason){
    case LWS_CALLBACK_ESTABLISHED:
      l("Connection status: " + LWS_CALLBACK_ESTABLISHED);
      break;
    case LWS_CALLBACK_RECEIVE:
      data = Synapsis::parseInstruction(&in, &resultState, &resultLen);      
      if(resultState == 1) {
         dataW = libwebsocket_write(wsi, &data[LWS_SEND_BUFFER_PRE_PADDING], resultLen, LWS_WRITE_TEXT);  
         lall( "Data w: " +  dataW );
      }
      else if(resultState == 2) {
        dataW = libwebsocket_write(wsi, &data[LWS_SEND_BUFFER_PRE_PADDING], resultLen, LWS_WRITE_BINARY);  
        //lall("Data w " + dataW + ". RESULT: binary data");
      }
      else lall("Errore: istruzione non interpretata: result state  " + resultState);
      break;
    default:
      break;
    }
  return 0;
}
 int Synapsis::callback_streaming(struct libwebsocket_context *context,
                         struct libwebsocket *wsi,
                         enum libwebsocket_callback_reasons reason, void *user,
                         void *in, size_t len)
{    
        
     return 0;
}

unsigned char* Synapsis::parseInstruction(void ** in, int* resultState,int* resultLen) {
    return NULL;
  }
