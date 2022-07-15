CXX = g++
CXXFLAGS = -Wall -g
all: proj4 proj41

proj41: SkewHeap.o TypedHeap.o test1.cpp
	$(CXX) $(CXXFLAGS) TypedHeap.o SkewHeap.o test1.cpp -o proj41
proj4: SkewHeap.o TypedHeap.o test.cpp
	$(CXX) $(CXXFLAGS) TypedHeap.o SkewHeap.o test.cpp -o proj4

SkewHeap.o: SkewHeap.cpp SkewHeap.h
	$(CXX) $(CXXFLAGS) -c SkewHeap.cpp

TypedHeap.o: TypedHeap.cpp TypedHeap.h
	$(CXX) $(CXXFLAGS) -c TypedHeap.cpp

run:
	./proj4
val:
	valgrind ./proj4
clean:
	rm *.o*
	rm *~ 
run1:
	./proj41
val1:
	valgrind ./proj41


help:           
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##//'

target00:       ## type 'make run' to test SkewHeaps and 'make run1' to test typed heaps
	@echo does nothing

