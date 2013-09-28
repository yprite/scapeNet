CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm -lpcap
THLAGS = -lpthread

all: scan

scan: senser_main.o senser_networkScan.o
	$(CC) $(LDFLAGS) $(THLAGS) -o $@ $^


senser_main.o: senser_main.c senser_networkScan.h
	$(CC) $(CFLAGS) $(LDFLAGS) $(THLAGS) -c $<

senser_networkScan.o: senser_networkScan.c senser_networkScan.h
	$(CC) $(CFLAGS) $(LDFLAGS) $(THLAGS) -c $<


clean:
	rm -f *.o scan
