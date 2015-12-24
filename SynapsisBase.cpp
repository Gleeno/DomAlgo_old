/* 
 * File:   SynapsisBase.cpp
 * Author: teo
 * 
 * Created on December 13, 2015, 4:16 PM
 */

#include "SynapsisBase.hpp"

SynapsisBase::SynapsisBase() {
    this->settingsRaw = this->getJsonFromFile("configs/default.json");    
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

Json::Value SynapsisBase::getJsonFromFile(std::string source) {
    Json::Value v;
    Json::Reader r;
    if(!r.parse(this->getContFromFile(source),v,false))
        throw(errno);
return v;    
}

Json::Value SynapsisBase::getSettingsRaw() {
    return (this->settingsRaw);
}