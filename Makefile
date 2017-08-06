SHELL = /bin/sh
FILES = main.cpp gol.cpp
CFLAG = -Wall -g
LIBS = -lncurses

GOL:
	g++ ${FILES} -o "GoL" ${CFLAG} ${LIBS} -std=c++14

clean:
	rm -f ./*.o ./compiling_error.txt
