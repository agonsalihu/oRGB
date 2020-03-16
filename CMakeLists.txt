cmake_minimum_required(VERSION 3.5)
project(oRGB)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                        /usr/local/share/cmake
                        /usr/share/cmake
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS 
    "-O2 \
    -pthread \
    -pedantic \
    -Wall \
    -Wextra \
    -Wcast-align \
    -Wcast-qual \
    -Wdisabled-optimization \
    -Wformat=2 \
    -Winit-self \
    -Wlogical-op \
    -Wmissing-declarations \
    -Wnoexcept \
    -Woverloaded-virtual \
    -Wredundant-decls \
    -Wshadow \
    -Wsign-promo \
    -Wstrict-null-sentinel \
    -Wstrict-overflow=5 \
    -Wswitch-default \
    -Wundef \
    -Werror \
    -Wno-unused"
)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
    include/
)

add_library(    
    ${PROJECT_NAME}
    src/wrapper.cpp
)

add_executable( 
    ${PROJECT_NAME}_exec
    src/main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}_exec
    ${PROJECT_NAME}
    ${OpenCV_LIBRARIES}
)

#add_subdirectory(test)