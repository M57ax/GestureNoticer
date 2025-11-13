cmake_minimum_required(VERSION 3.16)
project(GestureNoticer CXX)

# C++-Standard & Warnungen
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Falls nötig: Pfad zu deiner OpenCV-Config (ANPASSEN!)
set(OpenCV_DIR "C:/Users/maxis/Desktop/VSCprojekte/opencv/build")  # enthält OpenCVConfig.cmake

find_package(OpenCV )

# Includes & Executable
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(GestureNoticer main.cpp
) 
add_custom_command(TARGET GestureNoticer POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${CMAKE_SOURCE_DIR}/assets"
          "$<TARGET_FILE_DIR:GestureNoticer>/assets")

# Link gegen OpenCV
target_link_libraries(GestureNoticer PRIVATE ${OpenCV_LIBS})
