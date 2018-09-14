router.out : router.o RouterRunner.o BinaryHeap.o  
	g++ -ansi -Wall -g -pg -o router.out router.o RouterRunner.o BinaryHeap.o  

router.o : router.cpp router.h RouterRunner.h 
	g++ -ansi -Wall -g -c router.cpp

RouterRunner.o : RouterRunner.cpp CPUTimer.h RouterRunner.h router.h 
	g++ -ansi -Wall -g -c RouterRunner.cpp

BinaryHeap.o : BinaryHeap.cpp BinaryHeap.h 
	g++ -ansi -Wall -g -c BinaryHeap.cpp

clean : 
	rm -f router.out router.o  RouterRunner.o BinaryHeap.o gmon.out
