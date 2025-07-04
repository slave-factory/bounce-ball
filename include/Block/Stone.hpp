#ifndef STONE_HPP
#define STONE_HPP

#include "Block.hpp"

class Stone : public Block {

    public : 
        // Block의 생성자 사용
        Stone(float x, float y, float width, float height, float blockSize);     

};

#endif