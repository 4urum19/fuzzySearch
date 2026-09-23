CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic
TARGET   := fuzzySearch
SOURCES  := fuzzySearch.cpp

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

run: $(TARGET)
	./$(TARGET) .

clean:
	rm -f $(TARGET)