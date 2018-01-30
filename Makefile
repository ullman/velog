PREFIX= /usr/local
BINDIR= $(PREFIX)/bin
TARGET= velog
CC	= gcc
SRCDIR = src
CFLAGS = -c -O2 -Wall
LDFLAGS = 
#XCFLAGS = `pkg-config --cflags gtk+-3.0`
#XLDFLAGS = `pkg-config --libs gtk+-3.0`
SOURCES= $(SRCDIR)/velog.c $(SRCDIR)/serial.c
OBJECTS=$(SOURCES:.c=.o)


all: $(TARGET)

velog: $(SRCDIR)/velog.o $(SRCDIR)/serial.o
	$(CC) $(LDFLAGS) $(SRCDIR)/velog.o $(SRCDIR)/serial.o -o $@

install: all
	install -D $(TARGET) $(BINDIR)/$(TARGET)

uninstall: all
	  -rm $(BINDIR)/$(TARGET)
.c.o:
	$(CC) $(CFLAGS) $(XCFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
	rm -f $(OBJECTS)

.PHONY: all clean
