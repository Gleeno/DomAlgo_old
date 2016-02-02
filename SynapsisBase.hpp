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
#include <json/json.h>
#include "Synapsis/message/en.hpp"
class SynapsisBase {
public:
    SynapsisBase();
    SynapsisBase(const SynapsisBase& orig);
    virtual ~SynapsisBase();
    std::string getContFromFile(std::string source);
    static Json::Value getJson(char type,std::string* sourceOrPath);
    Json::Value getSettingsRaw();
protected:
    static Json::Value settingsRaw;
};

#endif	/* SYNAPSISBASE_HPP */

