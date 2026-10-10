# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I./src
LDFLAGS = 

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = .

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TARGET = $(BIN_DIR)/hospital_system.exe

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)

# Debug
debug: CXXFLAGS += -O0 -g
debug: $(TARGET)

# Release
release: CXXFLAGS += -O2 -DNDEBUG
release: $(TARGET)

.PHONY: all clean run debug release