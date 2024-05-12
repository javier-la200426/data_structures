#########################################################
#             PROJECT 4: Gerp Makefile             #
#########################################################
# COMP 15 Project 4: Gerp
# 
# Edited by Javier Laveaga (jlavea01) and Eva Caro (ecaro01) 
# Thursday, November 15.

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow 
LDFLAGS  = -g3 

gerp: main.o stringProcessing.o HashT.o DirNode.o Gerper.o FSTree.o
	$(CXX) $(CXXFLAGS) -o gerp $^

Gerper.o: Gerper.cpp Gerper.h HashT.h stringProcessing.h
	$(CXX) $(CXXFLAGS) -c Gerper.cpp

traverse_exec: FSTree.o DirNode.o FSTreeTraversal.o
	$(CXX) $(CXXFLAGS) -o traverse_exec $^ 

FSTreeTraversal.o: FSTreeTraversal.cpp FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp



unit_test: unit_test_driver.o stringProcessing.o HashT.o Gerper.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) $^

HashT.o: HashT.cpp HashT.h 
	$(CXX) $(CXXFLAGS) -c HashT.cpp

main.o: main.cpp Gerper.h HashT.h stringProcessing.h
	$(CXX) $(CXXFLAGS) -c main.cpp

stringProcessing.o: stringProcessing.cpp stringProcessing.h
	${CXX} ${CXXFLAGS} -c stringProcessing.cpp

clean: 
	rm -f gerp


	







