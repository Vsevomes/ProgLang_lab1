cmake_minimum_required(VERSION 3.16)
project(ProgLangLab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(/usr/local/include/antlr4-runtime)
link_directories(/usr/local/lib)

# Пути к исходникам
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(GEN_DIR ${CMAKE_SOURCE_DIR}/generated)

# Собираем все исходники
file(GLOB_RECURSE SRC_FILES
    ${SRC_DIR}/*.cpp
    ${GEN_DIR}/*.cpp
)

add_executable(ProgLangLab1 ${SRC_FILES} main.cpp)

# Включаем директории с заголовками
target_include_directories(ProgLangLab1 PRIVATE
    ${SRC_DIR}
    ${GEN_DIR}
)

# Линкуем antlr4-runtime
target_link_libraries(ProgLangLab1 PRIVATE antlr4-runtime)

# Опционально: показать все предупреждения
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(ProgLangLab1 PRIVATE -Wall -Wextra -Wpedantic)
endif()
