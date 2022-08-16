cmake_minimum_required(VERSION 3.22)
project(Spectrum)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/pkg/qt/5.12.8/gcc_64/lib/cmake")

include_directories(
        ${PROJECT_SOURCE_DIR}/inc
        ${PROJECT_SOURCE_DIR}/sources/headers
#        /usr/local/include
)

link_directories(
        /usr/local/lib
        /usr/lib/x86_64-linux-gnu
)
#find_path(LIBIIO libiio.h)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        PrintSupport
        REQUIRED)

add_executable(Spectrum main.cpp
        sources/device_config.cpp
        sources/headers/device_config.h sources/forms/device_config.ui inc/iio/iio_device_scan.hpp
        src/iio_device_scan.cpp inc/qt/thread_iio.hpp src/thread_iio.cpp
        inc/qt/qcustomplot.h src/qcustomplot.cpp
        inc/fft/fftw3.h sources/selectnumber.cpp sources/headers/selectnumber.h
        inc/iio/ad9361.h sources/headers/dial_change.h sources/dial_change.cpp)

target_link_libraries(Spectrum
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::PrintSupport
        libiio.so
        libfftw3.a
        libad9361.so
        boost_system
        )

