CC := clang++


# TODO: Header depend

CPPFLAGS  := -g -Wall -Wextra -pedantic
  
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
TEST_DIR := test
OUT_DIR := out

TARGET := rt
TEST_OUT := test


# TODO: Probably want to substitute rt and test.o to TARGET and TEST_OUT
SRC := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

TEST := $(shell find $(TEST_DIR) -name "*.cpp")
TEST_OBJ := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/test/%.o, $(TEST))
TEST_OBJ := $(filter-out $(BUILD_DIR)/rt.o, $(OBJ) $(TEST_OBJ))

all: $(TARGET) $(TEST_OUT)

$(TARGET): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(OUT_DIR)/$(TARGET)

$(TEST_OUT): $(TEST_OBJ)
	$(CC) $(CPPFLAGS) $(TEST_OBJ) -o $(OUT_DIR)/$(TEST_OUT)

$(BUILD_DIR)/test/%.o: $(TEST_DIR)/%.cpp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf build/*
