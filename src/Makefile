CFLAGS = -fPIC -O3 -g -Wall -Werror
CC = gcc

all:
	$(CC) $(CFLAGS) -c bp-monitor.cpp
	$(CC) -shared -Wl,-soname,libbpmonitor.so -o libbpmonitor.so bp-monitor.o

clean:
	$(RM) *.d *.o *.so* 
