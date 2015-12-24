/* 
 * File:   SynapsisBase.hpp
 * Author: teo
 *
 * Created on December 13, 2015, 4:16 PM
 */

#ifndef SYNAPSISBASE_HPP
#define	SYNAPSISBASE_HPP
#include <string>
#include <fstream>
#include <cerrno>
#include "Log.hpp"
#include "Synapsis/json/json.h"
class SynapsisBase {
public:
    SynapsisBase();
    SynapsisBase(const SynapsisBase& orig);
    virtual ~SynapsisBase();
    std::string getContFromFile(std::string source);
    Json::Value getJsonFromFile(std::string source);
    Json::Value getJson(std::string* source);
    Json::Value getSettingsRaw();
private:
    Json::Value settingsRaw;
};

#endif	/* SYNAPSISBASE_HPP */

