#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "../include/Block/Block.hpp"
#include "../include/Ball.hpp"

#include "../include/StageManager.hpp"
#include "../include/button.hpp"
#include "../include/stageMenu.hpp"

/**
 *  구현 고려해야하는 부분
 * 
 *  1. 스테이지마다 공의 위치 초기화
 *  2. 좌우 벽에 부딪혔을 때 좌우 이동 잠깐 동안 안 되게 하기   ==> 너무 딱따구리가 되어버림
 *  4. 블록 삭제 손 보기
 *  6. 게임이 끝났을 때 화면 생각하기
 *  7. 죽었을 때 별 리셋
 *  8. Map.hpp랑 Map.cpp 삭제해도 괜찮음
 **/

int main() {

    // 기본 요소
    sf::RenderWindow window;
    window.setVerticalSyncEnabled(true);
    window.create(sf::VideoMode(2048, 1024), "Bounce Ball");

    sf::Vector2i pixelPos;       // 픽셀 좌표
    sf::Vector2f mousePos;
    
    sf::Clock clock;
    int starCount = 0;
    bool inStage = false;
    int selectedStage;

    float windowWidth = 2048.0, windowHeight = 1024.0;

    // JSON 파일 기반으로 맵과 공 생성
    StageManager stageManager = StageManager("resource/stage/stages.json");
    std::vector<std::unique_ptr<Block>> blockList;
    Ball ball = Ball();

    // 배경 생성 => 칸 계산 좀 쉽게 하려고
    Block backGround = Block(0.f, 0.f, 32, 16, 128.f, "resource/image/BackGround.png");

    stageMenu stages = stageMenu();
    std::vector<button> buttonList = stages.getButtonList();

    while (window.isOpen()) {


        // delta time으로 계산
        float dt = clock.restart().asSeconds();

        sf::Event event;

        window.clear();   
        if (!inStage) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    pixelPos = sf::Mouse::getPosition(window);
                    mousePos = window.mapPixelToCoords(pixelPos);

                    for (int i = 0; i < buttonList.size(); ++i) {
                        if (buttonList[i].isClicked(mousePos, selectedStage)) {
                            inStage = true;
                            selectedStage = i + 1;
                            blockList = stageManager.getMap(i + 1);
                            ball.setStartSetting(stageManager.getStartingPosition(i + 1));
                            starCount = stageManager.getStarCount(i + 1);
                            break;
                        }
                    }
                }
            }
            
            for (const auto& b : buttonList) {
                b.render(window);
            }
        }
        else {
            // 배경 그리기
            window.draw(backGround);
    
            if (starCount == 0) {
                inStage = false;
                continue;
            }

            //블럭 그리기
            for (const auto& block : blockList) {
                if ((*block).isDraw) {
                    window.draw(*block);
                }
            }
    
            // while로 하면 delta 반영 X
            if (ball.getIsStraight()) {
                ball.moveHorizontal(dt);
            }
    
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                ball.setVelocityX(-230.f);
                ball.moveHorizontal(dt);
                ball.setIsStraight(false);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                ball.setVelocityX(230.f);
                ball.moveHorizontal(dt);
                ball.setIsStraight(false);
            }
    
            // 공 그리기
            ball.updatePosition(dt, blockList, starCount);
            window.draw(ball);
        }

        window.display();
    }

    return 0;

}