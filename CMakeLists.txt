# cmake_minimum_required(VERSION <specify CMake version here>)
project(C51_GameBoy C)

set(CMAKE_C_STANDARD 99)

add_executable(C51_GameBoy main.c eat_snake/EatSnake.h eat_snake/EatSnake.c delay_tool/DelayTool.h delay_tool/DelayTool.c gpu/GPU.h gpu/GPU.c game_pad/RedRemote.c game_pad/RedRemote.h)