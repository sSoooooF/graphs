#include "Graph.h"
#include "exercise1.h"
#include "exercise2.h"
#include "exercise3.h"
#include "exercise4.h"
#include "exercise5.h"
#include "exercise6.h"
#include "exercise7.h"
#include "exercise8.h"
#include "exercise9.h"
#include "exercise10.h"
#include "exercise11.h"
#include <iostream>
#include "map.h"

void main(int argc, const char* argv[])
{
	setlocale(LC_ALL, "rus");
	Graph graph;

	std::string filePath;
	bool useEdgesList = false;
	bool useMatrix = false;
	bool useAdjacencyList = false;

	int task = -1;

	for (int i = 1; i < argc; ++i) {
		std::string key = argv[i];
		std::string value = argv[i + 1];

		if (key == "-e") {
			filePath = value;
			useEdgesList = true;
			break;
		}
		else if (key == "-m") {
			filePath = value;
			useMatrix = true;
			break;
		}
		else if (key == "-l") {
			filePath = value;
			useAdjacencyList = true;
			break;
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
		graph.readGraphAdjacency(filePath);


	exercise9(graph, argc, argv);
}