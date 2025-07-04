#ifndef STONEBLOCK_HPP
#define STONEBLOCK_HPP

#include <SFML/Graphics.hpp>

class Block : public sf::Drawable, public sf::Transformable {

    public: 
        
        // 블록의 시작 위치 기준으로 사이즈 결정
        // blockSize는 최소 단위 블록 하나의 가로 세로 길이(정사각형)
        // width아 height는 실제 공간이 차지하는 픽셀 크기로 설정
        // x : 시작 위치 x, y : 시작 위치 y, width : 가로 블록 갯수, height : 세로 블록 갯수, blockSize : 블럭 1개 가로 세로 길이
        Block(float x, float y, float width, float height, float blockSize, std::string image);
                
        virtual ~Block() = default;

        // 경계
        sf::FloatRect boundary;

        // Draw 여부 확인
        bool isDraw;

        // Block 옮기기
        void moveBlock(float x, float y);
        
    protected :
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    private: 

        // 블록 전체 위치
        sf::Vector2f position;
        sf::Vector2f size;

        // 블록 한 개의 texture
        sf::Texture texture;

        // 합쳐진 block의 texture
        sf::RenderTexture renderTexture;

        // 화면에 그릴 sprite
        sf::Sprite sprite;

        int blockSize;

        void createRenderTexture();
};

#endif