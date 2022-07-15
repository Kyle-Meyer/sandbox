CXX = g++
CXXFLAGSS = -Wall

all: proj01 proj001 proj0001

proj01: maze.o test00.cpp
	$(CXX) $(CXXFLAGS) maze.o test00.cpp -o proj01
proj001: maze.o test01.cpp
	$(CXX) $(CXXFLAGS) maze.o test01.cpp -o proj001
proj0001: maze.o test02.cpp
	$(CXX) $(CXXFLAGS) maze.o test02.cpp -o proj0001

maze.o: maze.cpp maze.h
	$(CXX) $(CXXFLAGS) -c maze.cpp

run1:
	./proj01
run2:
	./proj001
run3:
	./proj0001
val1:
	valgrind ./proj01
val2:
	valgrind -s ./proj001
val3:
	valgrind -s ./proj0001
