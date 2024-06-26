cmake_minimum_required(VERSION 3.5)

project(visucpp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(FFTW3 REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport Concurrent)

set(PROJECT_SOURCES
        # Qt and GUI related files.
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        # Scan collection logic
        wfmcollection.hpp
        wfmcollection.cpp
        # File decode logic
        wfmcpp.h
        wfmcpp.cpp
        # QCustomPlot https://www.qcustomplot.com
        qcustomplot.cpp
        qcustomplot.h
)

# Find the FFTW3 library on the system to link against.
add_library(libfftw3 SHARED)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(visucpp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET visucpp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(visucpp SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(visucpp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Qt Required Links for QCustomPlot
target_link_libraries(visucpp PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(visucpp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(visucpp PRIVATE Qt${QT_VERSION_MAJOR}::Concurrent)
# FFTW Linkage
target_link_libraries(visucpp PRIVATE fftw3)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.visucpp)
endif()
set_target_properties(visucpp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS visucpp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(visucpp)
endif()
