## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libds.la
libds_la_SOURCES = ds.c ds.h

bin_PROGRAMS = ds
ds_SOURCES = ds_main.c
ds_CFLAGS = -std=c99 -Wall -g3
ds_LDADD = libds.la
