cmake_minimum_required(VERSION 3.0)
project(projet_neuron)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
add_subdirectory(gtest)
set(SOURCE_FILES
	main.cpp
        network.cpp
        network.hpp
        neuron.cpp
        neuron.hpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(projet_neuron ${SOURCE_FILES})
add_executable(neuron_unittest neuron.cpp neuron_unittest.cpp)

target_link_libraries(neuron_unittest gtest gtest_main)
add_test(neuron_unittest neuron_unittest)
