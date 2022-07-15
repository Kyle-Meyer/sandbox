CXX = g++
CXXFLAGS = -Wall

proj5: donut.h heap.h hash.h driver.cpp
	$(CXX) $(CXXFLAGS) donut.h heap.h hash.h driver.cpp -o proj5

clean:
	rm *.o*
	rm *~ 

run:
	./proj5
val:
	valgrind ./proj5


