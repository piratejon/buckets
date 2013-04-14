## Process this file with automake to produce Makefile.in

noinst_LTLIBRARIES = libds.la
libds_la_CFLAGS = -std=c99 -Wall -g3
libds_la_SOURCES = ds.c avl.c

bin_PROGRAMS = ds
ds_SOURCES = ds_main.c
ds_CFLAGS = -std=c99 -Wall -g3
ds_LDADD = libds.la
