#Variables 
CXX = g++
CXXFLAGS = -Wall

main: socketA.o
	$(CXX) -o main socketA.cc
