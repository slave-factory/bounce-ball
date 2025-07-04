cmake_minimum_required(VERSION 3.10)

project(
    CppProject
    VERSION 0.1
    DESCRIPTION "crossy-road-clone"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

# SFML 찾기
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# include 디렉토리 설정 (상대경로로 include/만 있으면 됩니다)
include_directories(${PROJECT_SOURCE_DIR}/include)

# src/ 안의 모든 .cpp 파일을 자동으로 수집
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# 실행 파일 생성
add_executable(main ${SOURCES})

# SFML 라이브러리 링크
target_link_libraries(main sfml-graphics sfml-window sfml-system)
