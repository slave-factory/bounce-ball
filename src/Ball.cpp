#include <iostream>
#include <memory>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Ball.hpp"

Ball::Ball() {

    ball.setRadius(16.f);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setFillColor(sf::Color(102,153,204));
}

// 공의 위치를 업데이트하는 함수
void Ball::updatePosition(float dt, std::vector<std::unique_ptr<Block>>& blockList, int& starCount) {

    sf::Vector2f initVelocity = velocity;

    // 기본적으로 중력 가속도 운동
    // isStraight 상태라면 중력 무시
    if (!getIsStraight()) {
        velocity.y += gravity.y * dt;
        position.y += initVelocity.y * dt + 0.5 * gravity.y * dt * dt;
    }

    // 화면을 벗어날 경우 원래 위치로 되돌리기
    if (position.y < 0 || position.y >= 1024.f || position.x < 0 || position.x > 2048) {
        position.x = startingPosition.x;
        position.y = startingPosition.y;
        setVelocityY(0.f);
        setVelocityX(0.f);
        setIsStraight(false);
    }

    // 블록과의 충돌 구현
    for (const auto& block : blockList) {

        sf::Vector2f blockCenter;
        sf::Vector2f delta;

        // 충돌 여부 판단 값
        blockCenter.x = ((*block).boundary.left + (*block).boundary.width / 2.f);
        blockCenter.y = ((*block).boundary.top + (*block).boundary.height / 2.f);

        delta = ball.getPosition() - blockCenter;

        float overlapX = ((*block).boundary.width / 2.f + ball.getRadius()) - std::abs(delta.x);
        float overlapY = ((*block).boundary.height / 2.f + ball.getRadius()) - std::abs(delta.y);


        if (auto starTemp = dynamic_cast<Star*>(block.get())) {
            if (ball.getGlobalBounds().intersects((*block).boundary)) {
                (*block).isDraw = false;

                // 먹은 별 삭제
                // 아 이걸 구현을 어떻게 해야하지, 버그는 안 나는데
                blockList.erase(remove(blockList.begin(), blockList.end(), block), blockList.end());
                starCount--;
                break;
            }
        }
        else if (auto breakalbeTemp = dynamic_cast<Breakalbe*>(block.get())) {
            if (ball.getGlobalBounds().intersects((*block).boundary)) {
                if (overlapX < overlapY) {
                    // 좌우 충돌
                    setIsStraight(false);
                    if (delta.x > 0) {  // 우
                        position.x += 750 * dt;
                    }
                    else {              // 좌
                        position.x -= 750 * dt;
                    }  
                } 
                else {
                    // 상하 충돌
                    if (delta.y > 0) {  // 하
                        setVelocityY(100.f);      // 아래쪽 벽에 부딪혔을 때는 떨어질 수 있게
                    }
                    else {              // 상
                        // 위쪽 벽에 부딪혔을 때는 위로 다시 튀길 수 있게
                        setVelocityY(-350.f);
                        blockList.erase(remove(blockList.begin(), blockList.end(), block), blockList.end());
                    }
                }
                break;
            }
        }
        else if (auto stoneTemp = dynamic_cast<Stone*>(block.get())) {
            if (ball.getGlobalBounds().intersects((*block).boundary)) {
                if (overlapX < overlapY) {
                    // 좌우 충돌
                    setIsStraight(false);
                    if (delta.x > 0) {  // 우
                        position.x += 750 * dt;
                    }
                    else {              // 좌
                        position.x -= 750 * dt;
                    }  
                } 
                else {
                    // 상하 충돌
                    if (delta.y > 0) {  // 하
                        setVelocityY(100.f);      // 아래쪽 벽에 부딪혔을 때는 떨어질 수 있게
                    }
                    else {              // 상
                        // 위쪽 벽에 부딪혔을 때는 위로 다시 튀길 수 있게
                        setVelocityY(-350.f);
                    }
                }
                break;
            }
        }
        else if (auto jumpTemp = dynamic_cast<Jump*>(block.get())) {       // 점프 블럭 충돌
            if (ball.getGlobalBounds().intersects((*block).boundary)) {
                if (overlapX < overlapY) {
                    // 좌우 충돌
                    setIsStraight(false);
                    if (delta.x > 0) {  // 우
                        position.x += 750 * dt;
                    }
                    else {              // 좌
                        position.x -= 750 * dt;
                    }  
                } 
                else {
                    // 상하 충돌
                    if (delta.y > 0) {  // 하
                        setVelocityY(100.f); 
                    }
                    else {              // 상
                        // 위쪽 벽에 부딪혔을 때는 위로 다시 튀길 수 있게
                        setVelocityY(-650.f);
                    }
                }
                break;
            }            
        }
        else if (auto straightTemp = dynamic_cast<Straight*>(block.get())) {
            if (ball.getGlobalBounds().intersects((*block).boundary)) {
                if (overlapX < overlapY) {
                    // 좌우 충돌
                    setIsStraight(false);           // 이 부분 수정 필수!!! 얘 때문에 직진이 쭉 안 된다
                    if (delta.x > 0) {  // 우
                        position.x += 750 * dt;
                    }
                    else {              // 좌
                        position.x -= 750 * dt;
                    }  
                } 
                else {
                    // 상하 충돌
                    if (delta.y > 0) {  // 하
                        setVelocityY(100.f); 
                    }
                    else {  // 상

                        setIsStraight(true);              // 공의 현재 상태 변경
                        if (straightTemp->getIsRight()) { // 가리키는 방향이 오른쪽이라면
                            position.x = straightTemp->boundary.left + 96.f;    // 공의 직진은 블록 앞에서
                            position.y = straightTemp->boundary.top + 32.f;
                            setVelocityY(0.f);
                            setVelocityX(400.f);
                        }
                        else {
                            position.x = straightTemp->boundary.left - 96.f;    // 공의 직진은 블록 앞에서
                            position.y = straightTemp->boundary.top + 32.f;
                            setVelocityY(0.f);
                            setVelocityX(-400.f);
                        }
                    }
                }
                break;
            }
        }
        else if (auto needleTemp = dynamic_cast<Needle*>(block.get())) {
            if (ball.getGlobalBounds().intersects((*block).boundary)) {
                if (overlapX < overlapY) {
                    // 좌우 충돌
                    setIsStraight(false);
                    if (delta.x > 0) {  // 우
                        position.x += 750 * dt;
                    }
                    else {              // 좌
                        position.x -= 750 * dt;
                    }  
                } 
                else {
                    // 상하 충돌
                    if (delta.y < 0) {  // 아래쪽에 부딪힐 일 없음 & 시작지점으로 돌아가기
                        position.x = startingPosition.x;
                        position.y = startingPosition.y;
                        setVelocityY(0.f);
                        setVelocityX(0.f);
                        setIsStraight(false);
                    }
                }
                break;
            }        
        }
    }

    ball.setPosition(position.x, position.y);

}

// 좌우 이동 속도 설정
void Ball::setVelocityX(float velocityX) {
    velocity.x = velocityX;
}

// y축 방향 이동 설정
void Ball::setVelocityY(float velocityY) {
    velocity.y = velocityY;
}

// 좌우 이동
void Ball::moveHorizontal(float dt) {
    position.x += velocity.x * dt;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(ball, states);   
}

// isStraight 판단
bool Ball::getIsStraight() {
    return isStraight;
}

void Ball::setIsStraight(bool isStraight) {
    this->isStraight = isStraight;
}

void Ball::setStartSetting(sf::Vector2f p) {

    position.x = p.x;
    position.y = p.y;
    startingPosition.x = p.x;
    startingPosition.y = p.y;

    gravity.x = 0.f;
    gravity.y = 700.f;

    setVelocityX(230.f);
    setVelocityY(0.f);

    setIsStraight(false);

}