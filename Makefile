CXX      = g++
CXXFLAGS = -std=c++17 -Wall
TARGET   = calculator
SRCS     = calculator.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)