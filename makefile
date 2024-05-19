#compile all classes for Project2 program

Project2 : term.o autocomplete.o SortingList.o Project2.o
	g++ *.o -o Project2

term.o : term.cpp term.h
	g++ -c term.cpp

autocomplete.o : autocomplete.cpp autocomplete.h
	g++ -c autocomplete.cpp

SortingList.o : SortingList.cpp SortingList.h
	g++ -c SortingList.cpp

Project2.o : Project2.cpp
	g++ -c Project2.cpp

clean : 
	rm -i *.o Project2

