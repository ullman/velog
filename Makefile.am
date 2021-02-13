ACLOCAL_AMFLAGS = -I m4
bin_PROGRAMS = velog vedirect_test
velog_SOURCES = \
	src/velog.c \
	src/serial.c src/serial.h \
	src/log_csv.c src/log_csv.h \
	src/vedirect.c src/vedirect.h \
	src/vedirect_devices.c \
	src/log_graphite.c src/log_graphite.h \
	src/log_prometheus.c src/log_prometheus.h

vedirect_test_SOURCES = \
	src/vedirect.c src/vedirect.h \
	src/vedirect_devices.c \
	src/vedirect_test.c
