## Process this file with automake to produce Makefile.in

TESTS = tests_avl tests_qt
check_PROGRAMS = tests_avl tests_qt
tests_avl_SOURCES = tests_main.c tests_avl.c $(top_builddir)/src/avl.h
tests_avl_CFLAGS = -Wall -g3 -std=c99 -I$(top_builddir)/src -I$(top_builddir)/tests
tests_avl_LDADD = $(top_builddir)/src/libds.la
tests_avl_LDFLAGS = -no-install

tests_qt_SOURCES = tests_main.c tests_qt.c $(top_builddir)/src/qt.h
tests_qt_CFLAGS = -Wall -g3 -std=c99 -I$(top_builddir)/src -I$(top_builddir)/tests
tests_qt_LDADD = $(top_builddir)/src/libds.la
tests_qt_LDFLAGS = -no-install

noinst_PROGRAMS = $(TESTS)

