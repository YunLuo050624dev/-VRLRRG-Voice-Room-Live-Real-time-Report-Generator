cmake_minimum_required(VERSION 3.15)
project(Voice-Room-Live-Real-time-Report-Generator)

add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Out)

add_executable(${PROJECT_NAME} WIN32 
    Src/main.cpp
    Src/TargetDialog.cpp
    Src/TimePickerDialog.cpp
)

target_link_libraries(${PROJECT_NAME} comctl32.lib)
