CXX = g++
CXXFLAGS = -Wall

proj5: Lqueue.h EReader.o Book.o
	$(CXX) $(CXXFLAGS) Lqueue.h EReader.o Book.o driver.cpp -o proj5

EReader.o: Lqueue.h Book.o EReader.h EReader.cpp
	$(CXX) $(CXXFLAGS) -c EReader.cpp

Book.o: Book.h Book.cpp
	$(CXX) $(CXXFLAGS) -c Book.cpp

run:
	./proj5 proj5_books.txt
val:
	valgrind ./proj5 proj5_books.txt
clean:
	rm *.o*
	rm *~ 
