###
### Makefile for CalcYouLater Project 2
### CalcYouLater is an RPN calculator
###
### Author:  Javier Laveaga (jlavea01)
### 10/22/2023

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# This is the linker rule that creates the executable
CalcYouLater: RPNCalc.o DatumStack.o Datum.o main.o parser.o
	${CXX} ${CXXFLAGS} -o CalcYouLater $^

main.o: main.cpp RPNCalc.h DatumStack.h Datum.h parser.h
	${CXX} ${CXXFLAGS} -c main.cpp

RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.h Datum.h
	${CXX} ${CXXFLAGS} -c RPNCalc.cpp

# This rule builds PassengerQueue.o
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	${CXX} ${CXXFLAGS} -c DatumStack.cpp

unit_test: unit_test_driver.o DatumStack.o RPNCalc.o Datum.o parser.o
	$(CXX) $(CXXFLAGS) $^

parser.o: parser.cpp parser.h
	${CXX} ${CXXFLAGS} -c parser.cpp


## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^

clean: 
	rm -f CalcYouLater