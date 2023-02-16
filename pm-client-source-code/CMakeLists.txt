cmake_minimum_required(VERSION 3.5)

project(pm-client-source-code VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        # MainWindow form files
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        # LogIn form files
        log_in_form.h log_in_form.cpp log_in_form.ui
        # Credits form files
        credits.h credits.cpp credits.ui
        # General settings
        general_settings.h general_settings.cpp general_settings.ui
        # i2p settings
        i2p_settings.h i2p_settings.cpp i2p_settings.ui
        # freenet settings
        freenet_settings.h freenet_settings.cpp freenet_settings.ui
        # Database application interface
        databaseAI.h databaseAI.cpp
        # Locales
        locales.h locales.cpp
        # Crypt class files
        cryptography.h cryptography.cpp
        # Src files
        source.qrc
)

# Check platforms
if (CMAKE_HOST_WIN32)
    # 32-разрядные поддерживаться не будут!
    set(WINDOWS64 1)
    #if (CMAKE_CL_64)
    #    set(WINDOWS64 1)
    #else ()
    #    set(WINDOWS32 1)
    #endif()
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

# Load platform version file
#if (WINDOWS64)
#    set(PROJECT_SOURCES ${PROJECT_SOURCES} databaseAI_win64.h databaseAI_win64.cpp)
#endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(pm-client-source-code
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET pm-client-source-code APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(pm-client-source-code SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(pm-client-source-code
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(pm-client-source-code PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(pm-client-source-code PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS pm-client-source-code
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pm-client-source-code)
endif()

#include_directories(aes256/)

if (WINDOWS64)
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        sqlite3/
        sqlite3-lib/win64/
        #aes256/
        #aes256/src/
    )
    target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
        sqlite3.a
    )
elseif (LINUX)
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        sqlite3/
        sqlite3-lib/linux/
        #aes256/
        #aes256/src/
    )
    target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
        sqlite3.a ${CMAKE_DL_LIBS}
    )
    #find_package(sqlite3 REQUIRED)

endif()
