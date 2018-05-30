###############################################################################
# GNU make file
# project:         web_connection_test
# author:          Dr. Lin, Chao
# since:           30th May 2018
# note:            requir curl library
###############################################################################


CC=gcc
CXX=g++
EXEC=web_conn
SRCS=$(wildcard *.cpp)
DEPS:=$(wildcard *.h)
OBJS:=$(patsubst %.cpp, %.o, $(wildcard *.cpp))

CFLAGS=-c -O2  -Wall -I/usr/local/include
LINKS=-O2 -L/usr/local/lib -lcurl

all:	$(EXEC)


help:
	@echo "================================================================================"
	@echo "GNU make file for web_connection_test"
	@echo "author:     Dr. Lin, Chao"
	@echo "since:      30th May 2018"
	@echo "================================================================================"
	@echo
	@echo "make        - build the code"
	@echo "make help   - show this help message"
	@echo "make clean  - clean object and executable files."


$(EXEC):	$(OBJS)
	$(CXX) $(LINKS) -o $(EXEC) $(OBJS)

%.o:	%.cpp $(DEPS)
	$(CXX) $(CFLAGS) $< -o $@




clean:
	-rm $(EXEC) $(OBJS)
	@echo "Clean done."
