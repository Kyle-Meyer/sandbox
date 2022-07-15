CXX = g++
CXXFLAGS = -Wall

lab7: StudentRecord.o lab7.cpp
	$(CXX) $(CXXFLAGS) StudentRecord.o lab7.cpp -o lab7

StudentRecord.o: StudentRecord.cpp StudentRecord.h
	$(CXX) $(CXXFlAGS) -c StudentRecord.cpp

clean:
	rm *.o*
	rm *~

run:
	./lab7
