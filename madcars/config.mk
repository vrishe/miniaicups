# The name of the executable to be created
BIN_NAME := madcars
# Compiler used
CXX ?= g++
# Extension of source files used in the project
SRC_EXT = cpp
# Path to the source directory, relative to the makefile
SRC_PATH = src
# Space-separated pkg-config libraries used by this project
LIBS =
# General compiler flags
COMPILE_FLAGS = -std=c++17 -Wall -Wextra -g
# Add additional include paths
INCLUDES = -I $(SRC_PATH) -I include -I dockers/cpp17
# General linker settings
LINK_FLAGS =