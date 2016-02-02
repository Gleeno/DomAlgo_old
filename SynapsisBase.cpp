/* 
 * File:   SynapsisBase.cpp
 * Author: teo
 * 
 * Created on December 13, 2015, 4:16 PM
 */

#include "SynapsisBase.hpp"

Json::Value SynapsisBase::settingsRaw;
SynapsisBase::SynapsisBase() {
    std::string configFile = "configs/default.json";
    this->settingsRaw = this->getJson( 'f', &configFile );
}

SynapsisBase::SynapsisBase(const SynapsisBase& orig) {
}

SynapsisBase::~SynapsisBase() {
}

std::string SynapsisBase::getContFromFile(std::string source) {
  std::ifstream in(source, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

Json::Value SynapsisBase::getSettingsRaw() {
    return (this->settingsRaw);
}
Json::Value SynapsisBase::getJson(char type, std::string* sourceOrPath){
    Json::Value v;
    Json::Reader r;
    if(type == 'f') {
        std::ifstream in(*sourceOrPath, std::ios::in | std::ios::binary);
        if (in) {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            if(!r.parse(contents,v,false))
                throw(errno);
        }
    }
    else {
         if(!r.parse(*sourceOrPath,v,false)) {
             lall("Instruction in bad format ( no json ). Exit");
             throw(errno);
         }
    }
    return v;
}