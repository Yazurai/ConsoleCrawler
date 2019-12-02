cmake_minimum_required(VERSION 3.15)
project(ConsoleCrawler C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(src/Enemy)
include_directories(src/GameUtilities)
include_directories(src/List)
include_directories(src/Player)
include_directories(src/UI)

add_executable(ConsoleCrawler
        src/Enemy/enemy.c
        src/Enemy/enemy.h
        src/GameUtilities/environment.c
        src/GameUtilities/environment.h
        src/GameUtilities/objects.h
        src/GameUtilities/position.h
        src/List/list.c
        src/List/list.h
        src/Player/playerController.c
        src/Player/playerController.h
        src/UI/escCodes.h
        src/UI/setupUI.c
        src/UI/setupUI.h
        src/UI/tickBox.c
        src/UI/tickBox.h
        src/UI/UIUtilies.c
        src/UI/UIUtilies.h
        src/main.c
        src/main.h)
