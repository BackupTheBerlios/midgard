%.c: %.pgc ; ecpg $<

CFLAGS=-I/usr/local/mingw/mingw32/include -I/usr/local/mingw/mingw32/include/local
CXXFLAGS=$(CFLAGS)

all: showreg.exe

CXXFLAGS=-g -I/usr/local/mingw/mingw32/include -I/usr/local/mingw/mingw32/include/local

launch.exe: launch.o registry.o launch_res.o
	gcc -mwindows -o launch.exe launch_res.o launch.o registry.o -lcomctl32

showreg.exe: showreg.o registry.o
	g++ -o showreg.exe showreg.o registry.o

filesel: filesel.o
	g++ -o filesel filesel.o -lcomdlg32

clean:
	rm -f *.o showreg.exe
