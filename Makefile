CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2
BUILD_DIR = build
BIN_DIR = bin

MAIN_SRC := main.cpp
MAIN_OBJ := $(BUILD_DIR)/main.o
MAIN_TARGET := torrent_test

TESTS := TestMyVector TestBencode
TEST_SRCS := $(addprefix tests/, $(addsuffix .cpp, $(TESTS)))
TEST_BINS := $(addprefix $(BIN_DIR)/, $(TESTS))
TEST_OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))

SRC := $(shell find . -name "*.cpp" ! -path "./tests/*" ! -name "main.cpp")
OBJ := $(patsubst ./%.cpp, $(BUILD_DIR)/%.o, $(SRC))

all: $(MAIN_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp $(shell find . -name "*.hpp")
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/%: tests/%.cpp $(filter-out $(MAIN_OBJ),$(OBJ))
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BUILD_DIR)/tests
	$(CXX) $(CXXFLAGS) -o $@ $^ -I.

run_%: $(BIN_DIR)/%
	./$<

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(MAIN_TARGET)
