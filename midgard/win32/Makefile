%.c: %.pgc ; ecpg $<

all: showreg.exe

CXXFLAGS=-g -I/usr/local/mingw/mingw32/include -I/usr/local/mingw/mingw32/include/local

showreg.exe: showreg.o registry.o
	g++ -o showreg.exe showreg.o registry.o

clean:
	rm -f *.o showreg.exe