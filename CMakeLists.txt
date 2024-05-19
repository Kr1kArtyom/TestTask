cmake_minimum_required(VERSION 3.21.3)
project(TestTask)

set(CMAKE_CXX_STANDARD 17)

# Указание каталога для заголовочных файлов
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Установка переменной для каталога с исходными файлами
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Указание, где искать заголовочные файлы
include_directories(${INCLUDE_DIR})

# Создание списка исходных файлов
set(SOURCES
    ${SRC_DIR}/Event.cpp 
    ${SRC_DIR}/MyTime.cpp
    ${SRC_DIR}/ComputerClub.cpp
    ${SRC_DIR}/Parser.cpp
    ${SRC_DIR}/Table.cpp
    ${SRC_DIR}/main.cpp
)

# Создание исполняемого файла
add_executable(task ${SOURCES})