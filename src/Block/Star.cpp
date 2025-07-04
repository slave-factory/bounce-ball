#include <iostream>
#include <SFML/Graphics.hpp>

#include "../../include/Block/Star.hpp"

Star::Star(float x, float y) 
    : Block(x,y, 1.f, 1.f,64.f,"resource/image/Star.png"){
}