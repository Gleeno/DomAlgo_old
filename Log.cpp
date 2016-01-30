/* 
 * File:   Log.cpp
 * Author: teo
 * 
 * Created on December 12, 2015, 2:24 PM
 */
#include "Log.hpp"
void l(std::string text) {
    std::cout << "** " << text <<" **" << std::endl;
}
void lf(std::string text, std::string fileName, std::string path) {
    time_t t= time(0);
    struct tm * now = localtime( & t );
    std::ofstream f;
    //l(path+fileName);
    f.open(path+fileName, std::fstream::app);
    
    //if(f.is_open()) l("file opened");
    //else l("Log file not opened");
    f << "Log: [ " 
          << now->tm_year + 1900 
          << "-"
          << now->tm_mon + 1 
          << "-"
          << now->tm_mday 
          << " at " 
          << now->tm_hour  
          << ":"
          << now->tm_min 
          << ":"
          << now->tm_sec 
          << " ] " 
          << text << std::endl;
    f.close();
}
void lall(std::string text, std::string fileName, std::string path) {
    l(text);
    lf(text, fileName, path);
}