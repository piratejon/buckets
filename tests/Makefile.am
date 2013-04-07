## Process this file with automake to produce Makefile.in

TESTS = tests_ds
check_PROGRAMS = tests_ds
tests_ds_SOURCES = tests_main.c tests_ds.c $(top_builddir)/src/ds.h
tests_ds_CFLAGS = -Wall -g3 -std=c99 -I$(top_builddir)/src -I$(top_builddir)/tests
tests_ds_LDADD = $(top_builddir)/src/libds.la
tests_ds_LDFLAGS = -no-install

noinst_PROGRAMS = $(TESTS)

