cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_PREFIX_PATH "${QTC_BUILD_PATH}")

project(Wakatime VERSION 1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(QtCreator REQUIRED COMPONENTS Core ProjectExplorer)

add_qtc_plugin(${PROJECT_NAME}
    PLUGIN_DEPENDS
        QtCreator::Core
        QtCreator::TextEditor
        QtCreator::ProjectExplorer
    DEPENDS
        QtCreator::ExtensionSystem
        QtCreator::Utils
    SOURCES
        src/ui/waka_options.ui
        src/ui/waka_options_page.cpp
        src/ui/waka_options_page.h
        src/ui/waka_options_widget.cpp
        src/ui/waka_options_widget.h
        src/waka_options.cpp
        src/waka_options.h
        src/waka_constants.h
        src/waka_global.h
        src/waka_plugin.cpp
        src/waka_plugin.h
        src/wakaworker.cpp
        src/wakaworker.h
        waka.qrc
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
target_compile_definitions(${PROJECT_NAME} PUBLIC WAKATIME_PLUGIN_VERSION="${CMAKE_PROJECT_VERSION}")
