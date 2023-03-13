cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)
project ("Patterns homework")
add_executable (CMakeTarget main.cpp
							units.h
							observer.h
							object.h
							logger.h)