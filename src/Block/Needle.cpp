#include <iostream>
#include <SFML/Graphics.hpp>

#include "../../include/Block/Needle.hpp"

Needle::Needle(float x, float y, float width, float height) 
    : Block(x,y + 0.5,width, height / 2, 64.f,"resource/image/Needle.png") {

}