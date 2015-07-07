
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/soccer)


set(CMAKE_AUTOMOC ON)

file(GLOB PLANNER_VISUALIZER_UIS "ui/*.ui")
qt5_wrap_ui(PLANNER_VISUALIZER_UIS ${PLANNER_VISUALIZER_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(PLANNER_VISUALIZER_SRC
    "main.cpp"
    "MainWindow.cpp"
    "PlannerVisualizerFieldView.cpp"
    "${PROJECT_SOURCE_DIR}/soccer/FieldBackgroundView.cpp"
    "${PROJECT_SOURCE_DIR}/common/Field_Dimensions.cpp"
)

add_executable(planner-visualizer ${PLANNER_VISUALIZER_SRC} ${PLANNER_VISUALIZER_UIS})
qt5_use_modules(planner-visualizer Widgets Xml Core Svg)
