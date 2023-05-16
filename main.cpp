#include "Graph.h"
#include "exercise1.h"
#include "exercise2.h"
#include "exercise3.h"
#include "exercise4.h"
#include <iostream>

void main(int argc, const char** argv)
{
	setlocale(LC_ALL, "rus");
	Graph graph;
	int index = 1;

	/*if (std::string(argv[index]) == "-m")
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
	}*/
	graph.readGraphMatrix("task4/matrix_t4_001.txt");
	exercise4(graph);
}