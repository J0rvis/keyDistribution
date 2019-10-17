#Variables 
CXX = g++
CXXFLAGS = -Wall

serverA: serverA.o
	$(CXX) -o main serverA.cc

nodeB: nodeB.o
	$(CXX) -o main nodeB.cc
