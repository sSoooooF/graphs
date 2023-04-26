#include "floydWarshall.h"
#include "Graph.h"
#include "exersice1.h"
#include <iostream>

const char* h = "-h";
const char* m = "-m";
const char* e = "-e";
const char* l = "-l";

void main(int argc, const char** argv)
{
	Graph graph;
	int index = 1;

	/*if (argv[index] == m)
	{
		graph.readGraphMatrix(argv[index+1]);
	}
	else if (argv[index] == e)
	{
		graph.readGraphEdges(argv[index+1]);
	}
	else if (argv[index] == l)
	{

	}
	else if (argv[index] == h)
	{
		help();
	}
	else {
		std::cout << "Error! Wrong parameter!\n";
		return;
	}*/
	graph.readGraphMatrix(argv[2]);
	exercise1(graph);
}