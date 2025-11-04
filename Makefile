CXX      = g++
CXXFLAGS = -std=c++17 -Wall
TARGET   = calculator
SRCS     = calculator.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) testcases.txt

clean:
	rm -f $(TARGET)