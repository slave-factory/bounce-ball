#include <iostream>
#include <SFML/Graphics.hpp>

#include "../../include/Block/Straight.hpp"

Straight::Straight(float x, float y, bool isRight) 
    : Block(x,y,1.f,1.f,64.f, 
        isRight ? "resource/image/StraightR.png" : "resource/image/StraightL.png"), isRight(isRight) {
}

bool Straight::getIsRight() {
    return isRight;
}