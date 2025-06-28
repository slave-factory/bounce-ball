cmake_minimum_required(VERSION 3.10)
project(bounce)

set(CMAKE_CXX_STANDARD 17)

# SFML 위치 자동 감지 or 수동 지정 가능
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(bounce src/main.cpp)

target_link_libraries(bounce sfml-graphics sfml-window sfml-system)
