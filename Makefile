SRCS = main.cpp device.cpp
OBJS = $(SRCS:.cpp=.o)

CXX = g++
CXXFLAGS = -g -std=c++14 -Wall

all: sim

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

sim: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	-rm -f sim $(OBJS)