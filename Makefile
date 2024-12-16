mytests: weightedGraph.o priorityQueue.o mytests.o
	g++ -std=c++17 -o mytests weightedGraph.o priorityQueue.o mytests.o

weightedGraph.o: weightedGraph.cpp weightedGraph.hpp
	g++ -std=c++17 -c weightedGraph.cpp

priorityQueue.o: priorityQueue.cpp priorityQueue.hpp
	g++ -std=c++17 -c priorityQueue.cpp

mytests.o: mytests.cpp weightedGraph.hpp
	g++ -std=c++17 -c mytests.cpp

clean:
	rm -f *.o mytests

run: mytests
	./mytests