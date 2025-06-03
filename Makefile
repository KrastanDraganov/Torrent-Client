CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2
BUILD_DIR = build
TARGET = torrent_test

SRC := $(shell find . -name "*.cpp")
OBJ := $(patsubst ./%.cpp, $(BUILD_DIR)/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp $(shell find . -name "*.hpp")
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
