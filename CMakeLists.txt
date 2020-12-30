cmake_minimum_required(VERSION 3.10)
project(Array VERSION 0.1.0 LANGUAGES C)

set(ARRAY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/array.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/array_io.c")
set(ARRAY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/array.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/array_io.h")
set(ARRAY_HEADER_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(ArrayExamples
    examples/main.c
    ${ARRAY_SOURCE_FILES}
)

target_include_directories(ArrayExamples PRIVATE ${ARRAY_HEADER_PATH})

message("Header Path : ${ARRAY_HEADER_PATH}")