CC := clang++

CPPFLAGS  := -g -Wall -Wextra -pedantic
  
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

TARGET := rt

SRC := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

all: $(TARGET)
  
$(TARGET): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(TARGET) 

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -c $< -o $@
