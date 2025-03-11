cmake_minimum_required(VERSION 3.16)

project(Whiteboard-B3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Core)
set(TS_FILES Whiteboard-B3_fr_FR.ts)

set(PROJECT_SOURCES
    main.cpp
    windows/mainwindow.cpp
    windows/mainwindow.h
    windows/mainwindow.ui
    windows/formulaireconnexion.cpp
    windows/formulaireconnexion.h
    windows/formulaireconnexion.ui
    windows/formulairehebergement.cpp
    windows/formulairehebergement.h
    windows/formulairehebergement.ui
    models/loghelper.h
    models/loghelper.cpp
    models/serveurtcp.h
    models/serveurtcp.cpp
    models/client.h
    models/client.cpp
    models/curseur.h
    models/idClient.h
    models/password.h
    models/curseurwidget.h
    models/curseurwidget.cpp
    windows/board.cpp
    windows/board.h
    resources.qrc

    ${TS_FILES}
)

include_directories(${CMAKE_SOURCE_DIR}/models)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-subsystem,console")
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Whiteboard-B3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Whiteboard-B3 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Whiteboard-B3 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Whiteboard-B3
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Whiteboard-B3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Network Qt6::Gui Qt6::Core)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Whiteboard-B3)
endif()
set_target_properties(Whiteboard-B3 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Whiteboard-B3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Whiteboard-B3)
endif()

