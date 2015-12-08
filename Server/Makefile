CC = gcc
INCLUDES = -I/usr/include/mysql
LIBS = -L/usr/lib/mysql -lmysqlclient

all: myserver

main.o: main.c server.h
	$(CC) -c $(INCLUDES) main.c

myserver: main.o
	$(CC) -o myserver main.o $(LIBS)

clean:
	rm -f myserver thunghiem.o 