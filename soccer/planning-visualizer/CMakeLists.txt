
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(PLANNER_VISUALIZER_SRC
    "main.cpp"
)

add_executable(planner-visualizer ${PLANNER_VISUALIZER_SRC})
target_link_libraries(planner-visualizer robocup)
