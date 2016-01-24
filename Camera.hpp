/* 
 * File:   Camera.hpp
 * Author: teo
 *
 * Created on January 7, 2016, 5:42 PM
 */

#ifndef CAMERA_HPP
#define	CAMERA_HPP

#include "SynapsisBase.hpp"


class Camera : public SynapsisBase {
public:
    Camera(std::string type);
    Camera(const Camera& orig);
    virtual ~Camera();
private:
    void ** camera;
};

#endif	/* CAMERA_HPP */

