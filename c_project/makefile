CFLAGS= -fopenmp -std=c11 -D_GNU_SOURCE -pedantic -Wall -Wextra -O2 `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0` `xml2-config --cflags` 
DFLAGS= `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0` `xml2-config --cflags` -std=c11 -pedantic -Wall -Wextra -O0 -g -fopenmp
LIBS=`xml2-config --libs` `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))
EXEC=program
CC=gcc
program:
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LIBS)
clean:
	rm $(EXEC) *.o 

debug: $(OBJS)
	$(CC) $(DFLAGS) -o $(EXEC) $(OBJS) $(LIBS)
	rm *.o
