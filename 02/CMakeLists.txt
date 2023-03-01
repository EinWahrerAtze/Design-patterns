cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)
project ("CPP_patterns_7.2")
add_executable (CMakeTarget main.cpp
							common.h
							units.h
							proxy.h
							decorator.h)