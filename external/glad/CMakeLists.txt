cmake_minimum_required(VERSION 3.15)

project(glad)

add_library(glad include/glad/glad.h src/glad.c)
# configure the include directories of glad
target_include_directories(glad PUBLIC include/)
