%.c: %.pgc ; ecpg $<

CFLAGS=-I/usr/local/mingw/mingw32/include -I/usr/local/mingw/mingw32/include/local

test_ecpg.exe: test_ecpg.o
	gcc -o test_ecpg.exe test_ecpg.o -lecpg -lpq -lwsock32

launch.exe: launch.o registry.o launch_res.o
	gcc -mwindows -o launch.exe launch_res.o launch.o registry.o

showreg.exe: showreg.o registry.o
	gcc -o showreg.exe showreg.o registry.o
clearreg.exe: clearreg.o registry.o
	gcc -o clearreg.exe clearreg.o registry.o

launch_res.o: launch.rc
	windres launch.rc launch_res.o

