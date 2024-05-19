cmake_minimum_required(VERSION 3.5)
project(YourProjectName)

# Установка переменной для каталога с заголовочными файлами
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Установка переменной для каталога с исходными файлами
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Указание, где искать заголовочные файлы
include_directories(${INCLUDE_DIR})

# Создание списка исходных файлов
set(SOURCES
    ${SRC_DIR}/Event.cpp
    ${SRC_DIR}/Time.cpp
    ${SRC_DIR}/ComputerClub.cpp
    ${SRC_DIR}/Parser.cpp
    ${SRC_DIR}/Table.cpp
    ${SRC_DIR}/main.cpp
)

# Создание исполняемого файла
add_executable(task ${SOURCES})