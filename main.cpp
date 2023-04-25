#include "floydWarshall.h"
#include "Graph.h"
#include "exersice1.h"
#include <iostream>


int main(int argc, char* argv[])
{
	Graph graph;
	int index = 1;

	//if (argv[index] == "-h") 
	//{

	//}
	//if (argv[index] == "-e") 
	//{
	//	graph.readGraphEdges(argv[index+1]);
	//}
	//if (argv[index] == "-m") 
	//{
	//	graph.readGraphMatrix(argv[index+1]);
	//}
	//if (argv[index] == "-l") 
	//{

	//}
	//graph.readGraphMatrix("C:/Users/nurie/source/repos/graphs/task1/matrix_t1_002.txt");
	graph.readGraphEdges("C:/Users/nurie/source/repos/graphs/task1/list_of_edges_t1_001.txt");
	exercise1(graph);

}