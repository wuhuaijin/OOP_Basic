CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

code : Basic/*.cpp
	$(CXX) -o code $^ $(CXXFLAGS)

clean:
	rm code -f

