#include <iostream>
#include <SFML/Graphics.hpp>


#include "../../include/Block/Stone.hpp"

Stone::Stone(float x, float y, float width, float height, float blockSize)  
    :Block(x ,y, width, height,blockSize,"resource/image/Stone.png"){

}