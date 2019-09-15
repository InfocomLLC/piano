CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(terminal_game)
SET (CMAKE_CXX_STANDARD 11)

SET(IncludedFiles include/rect_struct.h include/note.h include/play_screen.h
    include/piano.h)

SET (GameSourceFiles src/note.cpp src/play_screen.cpp src/piano.cpp src/main.cpp)

add_executable(piano ${GameSourceFiles})

include_directories(${CMAKE_ROOT_DIRECTORY} include)
target_link_libraries(piano -lncurses)
