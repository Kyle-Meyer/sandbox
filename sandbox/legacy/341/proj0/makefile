CXX = g++
CXXFLAGS = -Wall

all: proj00 proj01

proj00: my_array.o
	$(CXX) $(CXXFLAGS) my_array.o test0.cpp -o proj00

proj01:  my_array.o
	$(CXX) $(CXXFLAGS) my_array.o test1.cpp -o proj01

my_array.o: my_array.cpp my_array.h
	$(CXX) $(CXXFLAGS) -c my_array.cpp

clean:
	rm *.o*
	rm *~

val0:
	valgrind ./proj00
val1:
	valgrind -s ./proj01

run0:
	./proj00

run1:
	./proj01
