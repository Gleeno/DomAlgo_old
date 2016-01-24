/* 
 * File:   main.cpp
 * Author: teo
 *
 * Created on December 10, 2015, 4:26 PM
 */
#include "Synapsis.hpp"
#include "Log.hpp"
#include "Camera.hpp"
int main(int argc, char** argv) {
    lall("INIT");
    Synapsis *wsI = new Synapsis();
    Synapsis * wsSensors = new Synapsis();
    wsI->connect();  
    wsSensors->connect("127.0.0.1",9003);
    while (1) {
      lws_service(wsI->context, 50);      
      lws_service(wsSensors->context, 50);
    }
    return 0;
}

