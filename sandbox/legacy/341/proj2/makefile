CXX = g++
CXXFLAGS = -Wall

proj2: raq.o test.cpp
	$(CXX) $(CXXFLAGS) raq.o test.cpp -o proj2

raq.o: raq.h raq.cpp
	$(CXX) $(CXXFLAGS) -c raq.cpp


clean:
	rm *.o*
	rm *~ 

run:
	./proj2

val:
	valgrind ./proj2
