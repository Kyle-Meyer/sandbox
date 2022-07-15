CXX = g++
CXXFLAGS = -Wall

test: tester.o tester.cpp
	$(CXX) $(CXXFLAGS) tester.cpp -o test

clean:
	rm *.o*
	rm *~

run:
	./test
