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
    wsI->connect("127.0.0.1",9002);
    while (1) {
      lws_service(wsI->context, 50);
    }
    return 0;
}

