CC = gcc
INCLUDES = -I/usr/include/mysql
LIBS = -L/usr/lib/mysql -lmysqlclient

all: myserver

thunghiem.o: thunghiem.c 
	$(CC) -c $(INCLUDES) thunghiem.c

myserver: thunghiem.o
	$(CC) -o myserver thunghiem.o $(LIBS)

clean:
	rm -f myserver thunghiem.o 