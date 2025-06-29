cmake_minimum_required(VERSION 3.10)
project(bounce)

set(CMAKE_CXX_STANDARD 17)

# SFML 찾기
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# include 디렉토리 (현재는 src가 header 포함)
include_directories(src)

# 소스 파일 모음
file(GLOB SOURCES "src/*.cpp")

# 실행 파일 만들기
add_executable(bounce ${SOURCES})

# SFML 연결
target_link_libraries(bounce sfml-graphics sfml-window sfml-system)
