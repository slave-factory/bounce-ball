#ifndef STRAIGHT_HPP
#define STRAIGHT_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Block.hpp"

class Straight : public Block {

    public :
        Straight(float x, float y,bool isRight);
        bool getIsRight();
    private : 
        
        bool isRight;

};

#endif
