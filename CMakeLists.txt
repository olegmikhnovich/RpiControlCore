cmake_minimum_required(VERSION 3.12)
project(RpiControl)

set(CMAKE_CXX_STANDARD 17)

add_executable(RpiControl main.cpp src/audiocontrol.cpp src/audiocontrol.hpp utils/utils.cpp utils/utils.hpp src/connectivity.cpp src/connectivity.hpp src/deviceproperties.cpp src/deviceproperties.hpp src/filemanager.cpp src/filemanager.hpp src/searchdashboard.cpp src/searchdashboard.hpp)
