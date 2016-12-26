CC = g++
CFLAGS = -g -std=c++11 -Wall -fdiagnostics-color=always

default: tc

tc:  tcmain.o tcweapons.o
	$(CC) $(CFLAGS) -o tc tcmain.o tcweapons.o

tcmain.o:  tcmain.cc tcmain.h 
	$(CC) $(CFLAGS) -c tcmain.cc

tcweapons.o:  tcweapons.cc tcweapons.h 
	$(CC) $(CFLAGS) -c tcweapons.cc

clean: 
	$(RM) count *.o *~
