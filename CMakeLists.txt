cmake_minimum_required(VERSION 3.22)
project(Spectrum)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/opt/pkg/qt/5.12.8/gcc_64/lib/cmake")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/sources/headers
        /usr/local/include
)

link_directories(
        /usr/local/lib
        /usr/lib/x86_64-linux-gnu
        /usr/include
)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Spectrum main.cpp
        sources/device_config.cpp
        sources/headers/device_config.h sources/forms/device_config.ui)
target_link_libraries(Spectrum
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
#        gnuradio-qtgui
#        gnuradio-fft
#        gnuradio-blocks
#        gnuradio-analog
#        gnuradio-runtime
#        gnuradio-audio
        libiio.so
        boost_system
        )

