cmake_minimum_required(VERSION 3.12)
project(RpiControlCore)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)

add_executable(
        RpiControlCore
        main.cpp main.hpp
        utils/utils.cpp utils/utils.hpp
        src/audiocontrol.cpp src/audiocontrol.hpp
        src/connectivity.cpp src/connectivity.hpp
        src/deviceproperties.cpp src/deviceproperties.hpp
        src/filemanager.cpp src/filemanager.hpp
)

target_link_libraries(RpiControlCore ${CMAKE_THREAD_LIBS_INIT})
