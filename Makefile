all: adj 

adj: main.o MGS.o PGroup.o
	g++ main.o MGS.o PGroup.o -g -I. -I.. -o adj -lm

main.o: main.cpp MGS.h PGroup.h
	g++ -Wall -DHAVE_CONFIG_H -D_DEBUG -g -O2 -I. -I..  -c main.cpp

MGS.o: MGS.cpp MGS.h
	g++ -Wall -DHAVE_CONFIG_H -D_DEBUG -g -O2 -I. -I..  -c MGS.cpp

PGroup.o: PGroup.cpp PGroup.h
	g++ -Wall -DHAVE_CONFIG_H -D_DEBUG -g -O2 -I. -I..  -c PGroup.cpp

install:
	cp -f adj ../../bin/

clean:
	rm -rf *o adj 
