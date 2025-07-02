#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>

//! 게임 상태
enum class GameState {
    MainMenu = 0, //< 시작 메뉴
    WorldSelect = 1, //< 월드 선택 화면
    StageSelect = 2 //< 스테이지 선택 화면
};

GameState currentState = GameState::MainMenu;
int currentWorld = 0;

sf::Font font;

//! 버튼 구성
struct Button {
    sf::RectangleShape shape; //< 직사각형 모양
    sf::Text label; //< 텍스트
    std::function<void()> onClick; //< 버튼 클릭 시 실행 함수

    //! 버튼(shape and label) 그리기
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(label);
    }

    //! 마우스(mousePos)가 버튼 위에 있는지 확인
    bool isHovered(const sf::Vector2f& mousePos) {
        return shape.getGlobalBounds().contains(mousePos); //< 사각형의 경계(getGlobalBounds) 내부에 포함되어 있는지(contains) true or false return
    }

    //! 클릭 시 onClick() 실행
    void handleClick(const sf::Vector2f& mousePos) {
        if (isHovered(mousePos) && onClick)
            onClick();
    }
};

//! 버튼 종류
std::vector<Button> mainMenuButtons; //< 메인 메뉴
std::vector<Button> worldButtons; //< 월드
std::vector<Button> stageButtons; //< 스테이지

//! 버튼 세팅
void setupMainMenu();
void setupWorldSelect();
void setupStageSelect();

//! 메인 메뉴 세팅
void setupMainMenu() {
    mainMenuButtons.clear();

    //! start button
    Button startBtn;
    startBtn.shape.setSize({200, 60});
    startBtn.shape.setPosition(300, 200);
    startBtn.shape.setFillColor(sf::Color::Green);
    startBtn.label.setFont(font);
    startBtn.label.setString("Start");
    startBtn.label.setCharacterSize(30);
    startBtn.label.setFillColor(sf::Color::Black);
    startBtn.label.setPosition(360, 210);
    startBtn.onClick = []() {
        currentState = GameState::WorldSelect;
        setupWorldSelect(); //< WorldSelect로 이동
    };

    //! exit button
    Button exitBtn;
    exitBtn.shape.setSize({200, 60});
    exitBtn.shape.setPosition(300, 300);
    exitBtn.shape.setFillColor(sf::Color::Red);
    exitBtn.label.setFont(font);
    exitBtn.label.setString("Exit");
    exitBtn.label.setCharacterSize(30);
    exitBtn.label.setFillColor(sf::Color::Black);
    exitBtn.label.setPosition(370, 310);
    exitBtn.onClick = []() {
        exit(0); //< Program 종료
    };

    mainMenuButtons.push_back(startBtn);
    mainMenuButtons.push_back(exitBtn);
}

//! 월드 세팅
void setupWorldSelect() {
    worldButtons.clear();

    for (int i = 0; i < 3; ++i) { //< 3개 월드
        Button worldBtn;
        worldBtn.shape.setSize({150, 50});
        worldBtn.shape.setPosition(100.f + i * 160.f, 200);
        worldBtn.shape.setFillColor(sf::Color::Blue);
        worldBtn.label.setFont(font);
        worldBtn.label.setString("World " + std::to_string(i + 1));
        worldBtn.label.setCharacterSize(20);
        worldBtn.label.setFillColor(sf::Color::White);
        worldBtn.label.setPosition(worldBtn.shape.getPosition().x + 20, 210);

        worldBtn.onClick = [i]() {
            currentWorld = i + 1;
            currentState = GameState::StageSelect;
            setupStageSelect(); //< StageSelect로 이동
        };

        worldButtons.push_back(worldBtn);
    }

    Button backBtn;
    backBtn.shape.setSize({100, 40});
    backBtn.shape.setPosition(20, 20);
    backBtn.shape.setFillColor(sf::Color(100, 100, 100));
    backBtn.label.setFont(font);
    backBtn.label.setString("Back");
    backBtn.label.setCharacterSize(18);
    backBtn.label.setFillColor(sf::Color::White);
    backBtn.label.setPosition(30, 25);
    backBtn.onClick = []() {
        currentState = GameState::MainMenu;
        setupMainMenu(); //< 뒤로 가기(MainMenu)
    };

    worldButtons.push_back(backBtn);
}

//! 스테이지 세팅
void setupStageSelect() {
    stageButtons.clear();

    int rows = 3, cols = 5; //< 15개 스테이지
    for (int i = 0; i < rows * cols; ++i) {
        Button stageBtn;
        stageBtn.shape.setSize({100, 40});
        float x = 100 + (i % cols) * 120;
        float y = 100 + (i / cols) * 60;
        stageBtn.shape.setPosition(x, y);
        stageBtn.shape.setFillColor(sf::Color::Yellow);
        stageBtn.label.setFont(font);
        stageBtn.label.setString("Stage " + std::to_string(i + 1));
        stageBtn.label.setCharacterSize(18);
        stageBtn.label.setFillColor(sf::Color::Black);
        stageBtn.label.setPosition(x + 10, y + 10);
        stageBtn.onClick = [i]() {
            std::cout << "Load Stage " << i + 1 << " from World " << currentWorld << std::endl; //< i+1번째 스테이지
        };

        stageButtons.push_back(stageBtn);
    }

    Button backBtn;
    backBtn.shape.setSize({100, 40});
    backBtn.shape.setPosition(20, 20);
    backBtn.shape.setFillColor(sf::Color(100, 100, 100));
    backBtn.label.setFont(font);
    backBtn.label.setString("Back");
    backBtn.label.setCharacterSize(18);
    backBtn.label.setFillColor(sf::Color::White);
    backBtn.label.setPosition(30, 25);
    backBtn.onClick = []() {
        currentState = GameState::WorldSelect;
        setupWorldSelect(); //< 뒤로 가기(MainMenu)
    };

    stageButtons.push_back(backBtn);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bounce Ball Menu Test");

    //! 시스템 폰트 경로 로딩
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "font loading error\n";
        return 1;
    }

    //! 초기 화면 설정
    setupMainMenu();

    while (window.isOpen()) { //< 열려 있는 동안
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) //< 창 닫을 때
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) { //< 버튼 누를 때
                auto mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

                if (currentState == GameState::MainMenu)
                    for (auto& btn : mainMenuButtons) //< ranged-based for loop, 벡터 순회(반복)하기
                        btn.handleClick(mousePos);
                else if (currentState == GameState::WorldSelect)
                    for (auto& btn : worldButtons)
                        btn.handleClick(mousePos);
                else if (currentState == GameState::StageSelect)
                    for (auto& btn : stageButtons)
                        btn.handleClick(mousePos);
            }
        }

        window.clear(sf::Color::Black); //< 화면 초기화

        if (currentState == GameState::MainMenu)
            for (auto& btn : mainMenuButtons)
                btn.draw(window);
        else if (currentState == GameState::WorldSelect)
            for (auto& btn : worldButtons)
                btn.draw(window);
        else if (currentState == GameState::StageSelect)
            for (auto& btn : stageButtons)
                btn.draw(window);

        window.display(); //< 화면 노출
    }

    return 0;
}