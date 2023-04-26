#include "floydWarshall.h"
#include "Graph.h"
#include "exersice1.h"
#include <iostream>


void main(int argc, char* argv[])
{
	Graph graph;
	int index = 1;
	if (argv[index] == "-m")
	{
		graph.readGraphMatrix(argv[index + 1]);
	}
	else if (argv[index] == "-e")
	{
		graph.readGraphEdges(argv[index + 1]);
	}
	else if (argv[index] == "-l")
	{

	}
	else if (argv[index] == "-h")
	{
		help();
	}
	else {
		std::cout << "Error! Wrong parameter!\n";
		system("pause");
		return;
	}
	exercise1(graph);
}