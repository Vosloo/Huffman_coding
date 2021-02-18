# C++ compiler
CXX = clang++

# Compiler flags
CXXFLAGS += -Wall -std=c++17 -g

# Creating build dir
MKDIR_P = mkdir -p build

# cpp files
SOURCES := src/*.cpp

# hpp files
HEADERS := src/*.hpp

OUTPUT = build/main

# All depends on output
all: $(OUTPUT)

# The output depends on sources and headers
$(OUTPUT): $(SOURCES) $(HEADERS)
	$(MKDIR_P)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SOURCES)

clean:
	$(RM) $(OUTPUT)