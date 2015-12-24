/* 
 * File:   Log.hpp
 * Author: teo
 *
 * Created on December 12, 2015, 2:24 PM
 */

#ifndef LOG_HPP
#define	LOG_HPP
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>



void l(std::string text);
void lf(std::string text, std::string fileName="log", std::string path="logs/");
void lall(std::string text, std::string fileName="log", std::string path="logs/");

//deprecated
void l(std::ostringstream* text);
void lf(std::ostringstream text, std::string fileName="log", std::string path="logs/");
void lall(std::ostringstream text, std::string fileName="log", std::string path="logs/");
#endif	/* LOG_HPP */

