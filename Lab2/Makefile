CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -O2
AR := ar
ARFLAGS := rcs
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
LIB_DIR := $(BUILD_DIR)/lib
BIN_DIR := $(BUILD_DIR)/bin
LIB := $(LIB_DIR)/libcalc.a
APP := $(BIN_DIR)/calculator
SRCS := src/main.cpp src/calc.cpp
OBJS := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean dirs

all: dirs $(LIB) $(APP)

dirs:
	@mkdir -p $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)

$(OBJ_DIR)/%.o: src/%.cpp include/calc.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB): $(OBJ_DIR)/calc.o
	$(AR) $(ARFLAGS) $@ $^

$(APP): $(OBJ_DIR)/main.o $(LIB)
	$(CXX) $(CXXFLAGS) $< -L$(LIB_DIR) -lcalc -o $@

clean:
	@rm -rf $(BUILD_DIR)
