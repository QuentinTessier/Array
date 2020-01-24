cmake_minimum_required(VERSION 3.10)
project(Array VERSION 0.1.0 LANGUAGES C)

add_library(libArray
    src/array.c
    src/array.h
)