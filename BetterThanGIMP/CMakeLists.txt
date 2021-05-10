cmake_minimum_required(VERSION 3.19)
project(BetterThanGIMP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)
set(CMAKE_PREFIX_PATH "/opt/Qt5.12.10/5.12.10/gcc_64/lib/cmake")

add_executable(${PROJECT_NAME} src/main.cpp src/display/Window.cpp src/display/Window.h src/display/workspace/Workspace.cpp src/display/workspace/Workspace.h src/display/toolMenu/ToolMenu.cpp src/display/toolMenu/ToolMenu.h src/display/optionsMenu/OptionsMenu.cpp src/display/optionsMenu/OptionsMenu.h src/display/menuBar/MenuBar.cpp src/display/menuBar/MenuBar.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
