/* 
 * File:   main.cpp
 * Author: teo
 *
 * Created on December 10, 2015, 4:26 PM
 */
#include "Synapsis.hpp"
#include "Log.hpp"
#include <boost/thread.hpp>
int main(int argc, char** argv) {
    lall("INIT");
    Synapsis *mainWs = new Synapsis();
    mainWs->connect();  
    while (1) {
      libwebsocket_service(mainWs->context, 50);
    }
    return 0;
}

