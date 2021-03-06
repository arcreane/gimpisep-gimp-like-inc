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

add_executable(${PROJECT_NAME} src/main.cpp src/display/Window.cpp src/display/Window.h src/display/workspace/Workspace.cpp src/display/workspace/Workspace.h src/display/drawingMenu/DrawingMenu.cpp src/display/drawingMenu/DrawingMenu.h src/display/optionsMenu/OptionsMenu.cpp src/display/optionsMenu/OptionsMenu.h src/display/menuBar/MenuBar.cpp src/display/menuBar/MenuBar.h src/manipulations/Manipulation.cpp src/manipulations/Manipulation.h src/manipulations/Monochrome/Monochrome.cpp src/manipulations/Monochrome/Monochrome.h src/manipulations/CannyEdge/CannyEdge.cpp src/manipulations/CannyEdge/CannyEdge.h src/component/Slider/Slider.cpp src/component/Slider/Slider.h src/manipulations/Panorama/Panorama.cpp src/manipulations/Panorama/Panorama.h src/manipulations/drawing/Brush/Brush.cpp src/manipulations/drawing/Brush/Brush.h src/manipulations/drawing/Drawing.cpp src/manipulations/drawing/Drawing.h src/manipulations/drawing/Circle/Circle.cpp src/manipulations/drawing/Circle/Circle.h src/manipulations/Erosion/Erosion.cpp src/manipulations/Erosion/Erosion.h src/manipulations/Dilatation/Dilatation.cpp src/manipulations/Dilatation/Dilatation.h src/manipulations/drawing/Box/Box.cpp src/manipulations/drawing/Box/Box.h src/manipulations/Blur/Blur.cpp src/manipulations/Blur/Blur.h src/manipulations/Brightness/Brightness.cpp src/manipulations/Brightness/Brightness.h src/manipulations/Resizing/Resizing.cpp src/manipulations/Resizing/Resizing.h src/component/Input/Input.cpp src/component/Input/Input.h src/manipulations/Contrast/Contrast.cpp src/manipulations/Contrast/Contrast.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
