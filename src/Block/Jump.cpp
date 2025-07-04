#include<SFML/Graphics.hpp>

#include "../../include/Block/Jump.hpp"

Jump::Jump(float x, float y) 
    : Block(x,y,1.f,1.f,64.f,"resource/image/Jump.png"){
}