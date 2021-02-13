PREFIX= /usr/local
BINDIR= $(PREFIX)/bin
TARGET= velog
TEST_TARGET= vedirect_test
CC	= gcc
SRCDIR = src
CFLAGS = -c -O2 -Wall
LDFLAGS =-lprom -lpromhttp -lmicrohttpd
SOURCES= $(SRCDIR)/velog.c $(SRCDIR)/serial.c $(SRCDIR)/log_csv.c $(SRCDIR)/vedirect.c $(SRCDIR)/vedirect_devices.c $(SRCDIR)/log_graphite.c $(SRCDIR)/log_prometheus.c $(SRCDIR)/vedirect_test.c
OBJECTS=$(SOURCES:.c=.o)


all: $(TARGET) $(TEST_TARGET)

velog: $(SRCDIR)/velog.o $(SRCDIR)/serial.o $(SRCDIR)/log_csv.o $(SRCDIR)/vedirect.o $(SRCDIR)/vedirect_devices.o $(SRCDIR)/log_graphite.o $(SRCDIR)/log_prometheus.o
	$(CC) $(LDFLAGS) $(SRCDIR)/velog.o $(SRCDIR)/serial.o $(SRCDIR)/log_csv.o $(SRCDIR)/vedirect.o $(SRCDIR)/vedirect_devices.o $(SRCDIR)/log_graphite.o $(SRCDIR)/log_prometheus.o -o $@

vedirect_test: $(SRCDIR)/vedirect.o $(SRCDIR)/vedirect_devices.o $(SRCDIR)/vedirect_test.o
	$(CC) $(LDFLAGS) -lcunit $(SRCDIR)/vedirect.o $(SRCDIR)/vedirect_devices.o $(SRCDIR)/vedirect_test.o -o $@

test: vedirect_test
	./vedirect_test

install: all
	install -D $(TARGET) $(BINDIR)/$(TARGET)

uninstall: all
	  -rm $(BINDIR)/$(TARGET)
.c.o:
	$(CC) $(CFLAGS) $(XCFLAGS) $< -o $@

clean:
	rm -f $(TARGET) $(TEST_TARGET)
	rm -f $(OBJECTS)

.PHONY: all clean
