#include "floydWarshall.h"
#include "Graph.h"
#include "exersice1.h"
#include <iostream>


int main(int argc, char* argv[])
{
	Graph graph;
	int index = 1;

	/*if (argv[index] == "-h") 
	{

	}
	if (argv[index] == "-e") 
	{
		graph.readGraphEdges(argv[index+1]);
	}
	if (argv[index] == "-m") 
	{
		graph.readGraphMatrix(argv[index+1]);
	}
	if (argv[index] == "-l") 
	{

	}*/
	graph.readGraphMatrix("C:/Users/nurie/source/repos/graphs/task1/matrix_t1_002.txt");
	exercise1(graph);

}