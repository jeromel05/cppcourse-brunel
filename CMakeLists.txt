cmake_minimum_required(VERSION 3.8)
project(projet_neuron)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        network.cpp
        network.hpp
        neuron.cpp
        neuron.hpp)

add_executable(projet_neuron ${SOURCE_FILES})