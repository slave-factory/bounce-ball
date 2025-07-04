#include <iostream>
#include <SFML/Graphics.hpp>

#include "../../include/Block/Breakable.hpp"

Breakalbe::Breakalbe(float x, float y) 
    : Block(x,y,1.f,1.f,64.f,"resource/image/Breakable.png") {

}