#########################################################
#             PROJECT 3: Zap Makefile             #
#########################################################
# COMP 15 Project 3: Zap
# 
# Edited by Javier Laveaga (jlavea01) Thursday, November 15.

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

zap: main.o HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o ZapUtil.o
	$(CXX) $(CXXFLAGS) -o zap $^

unit_test: unit_test_driver.o phaseOne.o ZapUtil.o HuffmanTreeNode.o HuffmanCoder.o BinaryIO.o
	$(CXX) $(CXXFLAGS) $^

clean: 
	rm -f zap

phaseOne.o: phaseOne.cpp phaseOne.h
	$(CXX) $(CXXFLAGS) -c phaseOne.cpp

main.o: main.cpp HuffmanCoder.h
	$(CXX) $(CXXFLAGS) -c main.cpp

HuffmanCoder.o: HuffmanCoder.h HuffmanCoder.cpp ZapUtil.h BinaryIO.h 
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp

# for testing the example file and seeing its output
#minpq_example: minpq_example.o HuffmanTreeNode.o
#$(CXX) $(CXXFLAGS) -o minpq_example minpq_example.o HuffmanTreeNode.o

#minpq_example.o: minpq_example.cpp HuffmanTreeNode.h
#$(CXX) $(CXXFLAGS) -c minpq_example.cpp




