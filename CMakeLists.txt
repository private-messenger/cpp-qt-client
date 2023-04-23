cmake_minimum_required(VERSION 3.5)

project(spik-source VERSION 0.1 LANGUAGES CXX)

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
        # key viewer form
        key-viewer.h key-viewer.cpp key-viewer.ui
        # Change passwod
        change-password.h change-password.cpp change-password.ui
        # Create chat
        create-chat.h create-chat.cpp create-chat.ui
        # Add contact
        add-contact.h add-contact.cpp add-contact.ui
        # Database application interface
        #databaseAI_legacy.h databaseAI_legacy.cpp
        databaseAI.h databaseAI.cpp
        # Server
        #run-server.h run-server.cpp
        # Locales
        locales.h locales.cpp
        # Choose language after setup
        #ch_lang.h ch_lang.cpp ch_lang.ui
        # Crypt class files
        cryptography.h cryptography.cpp
        # Src files
        source.qrc
        # Send message
        send-msg-thread.h send-msg-thread.cpp
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

if (WINDOWS64)
    set(PROJECT_SOURCES ${PROJECT_SOURCES}
        win-functions/create-process.cpp
        win-functions/create-process.h
        win-functions/nodejs-run.cpp
        win-functions/nodejs-run.h
    )
elseif (LINUX)
    set(PROJECT_SOURCES ${PROJECT_SOURCES}
        linux-functions/create-process.cpp
        linux-functions/create-process.h
        linux-functions/nodejs-run.cpp
        linux-functions/nodejs-run.h
    )
endif()

# Load platform version file
#if (WINDOWS64)
#    set(PROJECT_SOURCES ${PROJECT_SOURCES} databaseAI_win64.h databaseAI_win64.cpp)
#endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(spik-source
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET spik-source APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(spik-source SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(spik-source
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(spik-source PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(spik-source PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS spik-source
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(spik-source)
endif()

#include_directories(aes256/)

if (WINDOWS64)
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        sqlite3/
        sqlite3-lib/win64/
        win-functions/
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
        linux-functions/
        #aes256/
        #aes256/src/
    )
    target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
        sqlite3.a ${CMAKE_DL_LIBS}
    )
    #find_package(sqlite3 REQUIRED)

endif()
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
