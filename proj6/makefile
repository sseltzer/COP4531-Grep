#
# makefile for graph algorithms project
#

LIB     = /home/courses/cop4531p/fall14
CPP     = $(LIB)/cpp
TCPP    = $(LIB)/tcpp
AREA51  = $(LIB)/area51
PROJ    = .
INCPATH = -I$(PROJ) -I$(CPP) -I$(TCPP)

CC   = g++47 -std=c++11 -Wall -Wextra

all: clean grep.x perm

clean:
	-rm grep.x

grep.x: $(PROJ)/grep.h $(PROJ)/nfa.h
	$(CC) $(INCPATH) -ogrep.x grepdriver.cpp

perm:
	-chmod 700 grep.x

