#ifndef BALL_HPP
#define BALL_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Block/Block.hpp"
#include "Block/Stone.hpp"
#include "Block/Star.hpp"
#include "Block/Jump.hpp"
#include "Block/Straight.hpp"
#include "Block/Needle.hpp"
#include "Block/Breakable.hpp"

class Ball : public sf::Drawable, public sf::Transformable{

    public:

        Ball();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void updatePosition(float dt, std::vector<std::unique_ptr<Block>>& blockList, int& starCount);
        void moveHorizontal(float dt);
        
        bool getIsStraight();
        void setIsStraight(bool isStraight);
        void setVelocityX(float velocityX);
        void setVelocityY(float velocityY);
        void setStartSetting(sf::Vector2f p);
        
    private:
        sf::Vector2f position;
        sf::Vector2f startingPosition;
        sf::Vector2f gravity;
        sf::Vector2f velocity;

        sf::CircleShape ball;

        bool isStraight;

};

#endif