CFLAGS = -fPIC -O3 -Wall -Werror
CC = gcc

all:
	$(CC) $(CFLAGS) -c bp-monitor.cpp
	$(CC) -shared -Wl,-soname,libbpmonitor.so -o libbpmonitor.so bp-monitor.o

debug:
	$(CC) $(CFLAGS) -c bp-monitor.cpp -g -D _DEBUG
	$(CC) -shared -Wl,-soname,libbpmonitor.so -o libbpmonitor.so bp-monitor.o

clean:
	$(RM) *.d *.o *.so* 
