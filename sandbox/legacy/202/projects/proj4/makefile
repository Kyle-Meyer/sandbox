CXX = g++
CXXFLAGS = -Wall

proj4: War.o Horse.o Untrained.o Warhorse.o Light.o Medium.o Heavy.o driver.cpp
	$(CXX) $(CXXFLAGS) War.o Horse.o Untrained.o Warhorse.o Light.o Medium.o Heavy.o driver.cpp -o proj4

War.o: Horse.o Untrained.o Warhorse.o Light.o Medium.o Heavy.o War.cpp War.h
	$(CXX) $(CXXFLAGS) -c War.cpp

Horse.o: Untrained.o Warhorse.o Light.o Medium.o Heavy.o Horse.cpp Horse.h
	$(CXX) $(CXXFLAGS) -c Horse.cpp

Untrained.o: Untrained.h Untrained.cpp
	$(CXX) $(CXXFLAGS) -c Untrained.cpp

Warhorse.o: Light.o Medium.o Heavy.o Warhorse.h Warhorse.cpp
	$(CXX) $(CXXFLAGS) -c Warhorse.cpp

Light.o: Light.cpp Light.h
	$(CXX) $(CXXFLAGS) -c Light.cpp

Medium.o: Medium.cpp Medium.h
	$(CXX) $(CXXFLAGS) -c Medium.cpp

Heavy.o : Heavy.cpp Heavy.h
	$(CXX) $(CXXFLAGS) -c Heavy.cpp

run:
	./proj4 proj4_data.txt

val:
	valgrind -v ./proj4 proj4_data.txt
clean:
	rm *.o*
	rm *~
