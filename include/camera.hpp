#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>

class Camera
{
private:
    std::string type;
public:
    Camera(){}
    Camera(const char* type) : type(type){}
    ~Camera(){}

    inline std::string getType() {return type;}
    inline void setType(std::string nType) {type = nType;}
};


#endif