%.c: %.pgc ; ecpg $<

CFLAGS=-I/usr/local/mingw/mingw32/include -I/usr/local/mingw/mingw32/include/local

test_ecpg.exe: test_ecpg.o
	gcc -o test_ecpg.exe test_ecpg.o -lecpg -lpq -lwsock32

launch.exe: launch.o registry.o
	gcc -o launch.exe launch.o registry.o
