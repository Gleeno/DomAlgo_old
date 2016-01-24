/* 
 * File:   Camera.cpp
 * Author: teo
 * 
 * Created on January 7, 2016, 5:42 PM
 */

#include "Camera.hpp"
#include <opencv2/opencv.hpp>

Camera::Camera(std::string type)
: SynapsisBase(){
    if(type.compare(this->settingsRaw["GENERIC_CAM"].asString())) {
       //*this->camera = new cv::VideoCapture(0);        
    }
}

Camera::Camera(const Camera& orig) {
}

Camera::~Camera() {
}

