cmake_minimum_required(VERSION 3.15)
project(figure3D VERSION 0.0.4 LANGUAGES CXX)

add_library(figure3D src/figure3D.cpp)

target_include_directories(figure3D PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(figure3D PUBLIC cxx_std_17)
