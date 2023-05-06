#include "Graph.h"
#include "exercise1.h"
#include "exercise2.h"
#include "exercise3.h"
#include <iostream>

void main(int argc, const char** argv)
{
	Graph graph;
	int index = 1;

	if (std::string(argv[index]) == "-m")
	{
		graph.readGraphMatrix(argv[++index]);
	}
	else if (std::string(argv[index]) == "-e")
	{
		graph.readGraphEdges(argv[++index]);
	}
	else if (std::string(argv[index]) == "-l")
	{
		graph.readGraphAdjacency(argv[++index]);
	}
	else if (std::string(argv[index]) == "-h")
	{
		help();
	}
	else {
		std::cout << "Error! Wrong parameter!\n";
		return;
	}
	//graph.readGraphMatrix("task2/matrix_t2_002.txt");
	exercise1(graph);
}