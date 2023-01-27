cmake_minimum_required(VERSION 3.5)

project(autorent VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install" CACHE PATH "..." FORCE)
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)

set(PROJECT_SOURCES
        appwindow.cpp
        appwindow.h
        appwindow.ui
        authorization.cpp
        authorization.h
        authorization.ui
        main.cpp
        registration.cpp
        registration.h
        registration.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(autorent
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
     add_executable(autorent ${PROJECT_SOURCES})
endif()

target_link_libraries(autorent PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(autorent PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(autorent PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/carrent.db
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(autorent)
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
install(TARGETS autorent DESTINATION .)
install(FILES carrent.db
DESTINATION .)
