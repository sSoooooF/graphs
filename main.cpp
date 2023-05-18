#include "Graph.h"
#include "exercise1.h"
#include "exercise2.h"
#include "exercise3.h"
#include "exercise4.h"
#include "exercise5.h"
#include "exercise6.h"
#include <iostream>

void main(int argc, const char** argv)
{
	setlocale(LC_ALL, "rus");
	Graph graph;
	
	/*std::string filePath;
	bool useEdgesList = false;
	bool useMatrix = false;
	bool useAdjacencyList = false;

	for (int i = 1; i < argc; i += 2) {
		const char* key = argv[i];
		const char* value = argv[i + 1];

		if (strcmp(key, "-e")) {
			filePath = value;
			useEdgesList = true;
		}
		else if (strcmp(key, "-m")) {
			filePath = value;
			useMatrix = true;
		}
		else if (strcmp(key, "-l")) {
			filePath = value;
			useAdjacencyList = true;
		}
		else {
			std::cout << "Invalid argument!\n";
			return;
		}
	}

	if (useEdgesList + useMatrix + useAdjacencyList != 1) {
		std::cout << "Exactly one file format must be specified!\n";
		return;
	}

	if (useEdgesList)
		graph.readGraphEdges(filePath);
	if (useMatrix)
		graph.readGraphMatrix(filePath);
	if (useAdjacencyList)
		graph.readGraphAdjacency(filePath);*/

	graph.readGraphMatrix("C:/Users/nurie/source/repos/graphs/task6/matrix_t6_001.txt");

	exercise6(graph, argc, argv);
}