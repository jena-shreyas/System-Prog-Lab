SHELL = /bin/sh
CC = gcc
CFLAGS = -g -Wall
SRCFILE = main.c
EXECFILE = graph.out
LIB = -lgraph -lmyimpl 
INCLUDEDIR = /usr/include
LIBDIR = $(INCLUDEDIR)/lib


compile : 
	$(CC) -L$(LIBDIR) -o $(EXECFILE) $(SRCFILE) $(LIB)

