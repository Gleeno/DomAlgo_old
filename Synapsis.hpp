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


class Synapsis : public SynapsisBase {
public:
    Synapsis();
    Synapsis(const Synapsis& orig);
    virtual ~Synapsis();
    int connect(std::string address="127.0.0.1", int port=9002);
    static int callback_streaming(struct libwebsocket_context *context,
                         struct libwebsocket *wsi,
                         enum libwebsocket_callback_reasons reason, void *user,
                         void *in, size_t len);
    static int callback_instruction(struct libwebsocket_context *context,
                         struct libwebsocket *wsi,
                         enum libwebsocket_callback_reasons reason, void *user,
                         void *in, size_t len);
    static int callback_http(struct libwebsocket_context *context,
                         struct libwebsocket *wsi,
                         enum libwebsocket_callback_reasons reason, void *user,
                         void *in, size_t len);
    struct libwebsocket_context *context;
    static unsigned char* parseInstruction(void ** in, int* resultState,int* resultLen);
private:
    std::string wsAddress;
    int wsPort;
};

#endif	/* SYNAPSIS_HPP */

