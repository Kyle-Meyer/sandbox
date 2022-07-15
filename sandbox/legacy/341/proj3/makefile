CXX = g++
CXXFLAGS = -Wall


all: proj3 proj31 proj32 proj33

proj33: treap.o test4.cpp
	$(CXX) $(CXXFLAGS) treap.o test4.cpp -o proj33

proj32: treap.o test3.cpp
	$(CXX) $(CXXFLAGS) treap.o test3.cpp -o proj32

proj31: treap.o test2.cpp
	$(CXX) $(CXXFLAGS) treap.o test2.cpp -o proj31

proj3: treap.o test.cpp
	$(CXX) $(CXXFLAGS) treap.o test.cpp -o proj3

treap.o: treap.cpp treap.h
	$(CXX) $(CXXFLAGS) -c treap.cpp


clean:
	rm *.o*
	rm *~ 

run1:
	./proj3
val1:
	valgrind ./proj3
bug1:
	gdb proj3
time1:
	time ./proj3
run2:
	./proj31
val2:
	valgrind ./proj31
bug2:
	gdb proj31
time2:
	time ./proj31

run3:
	./proj32
val3:
	valgrind ./proj32
bug3:
	gdb proj32
time3:
	time ./proj32

run4:
	./proj33
val4:
	valgrind ./proj33
bug4:
	gdb proj33
time4:
	time ./proj33
