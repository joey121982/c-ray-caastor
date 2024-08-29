# Compiler
CXX = g++
PROJECT_ROOT = .

# SDL2 flags (these will add the necessary include paths and libraries)
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LDFLAGS = $(shell sdl2-config --libs)
SDL2_IMAGE_LDFLAGS = -lSDL2_image

BUILD_DIR = $(PROJECT_ROOT)/build

# Source and Object files directories
ASSET_DIR = $(PROJECT_ROOT)/assets
SRC_DIR = $(PROJECT_ROOT)/src
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
BUILD_ASSETS_DIR = $(BUILD_DIR)/assets

# Create list of all source files and corresponding object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Executable name
TARGET = $(BIN_DIR)/ccaastor

# Compiler flags
CXXFLAGS = -Wall -O2 -std=c++17 $(SDL2_CFLAGS)

# Default target
all: $(TARGET)

copy-assets:
	@mkdir -p $(BUILD_ASSETS_DIR)
	cp -r $(ASSET_DIR)/* $(BUILD_ASSETS_DIR)/

# Linking the final executable
$(TARGET): $(OBJS) 
	make copy-assets
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SDL2_LDFLAGS) $(SDL2_IMAGE_LDFLAGS)

# Compiling source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(BIN_DIR)/*
	rm -rf $(BUILD_ASSETS_DIR)/*

run:
	$(BIN_DIR)/ccaastor

# Phony targets
.PHONY: all clean run copy-assets
