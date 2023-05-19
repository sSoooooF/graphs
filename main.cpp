#include "Graph.h"
#include "exercise1.h"
#include "exercise2.h"
#include "exercise3.h"
#include "exercise4.h"
#include "exercise5.h"
#include "exercise6.h"
#include <iostream>

void main(int argc, const char* argv[])
{
	setlocale(LC_ALL, "rus");
	Graph graph;
	
	std::string filePath;
	bool useEdgesList = false;
	bool useMatrix = false;
	bool useAdjacencyList = false;

	int task = -1;

	//for (int i = 1; i < argc; ++i)
	//{
	//	std::string key = argv[i];

	//	if (key == "-t1")
	//		task = 1;
	//	else if (key == "-t2")
	//		task = 2;
	//	else if (key == "-t3")
	//		task = 3;
	//	else if (key == "-t4")
	//		task = 4;
	//	else if (key == "-t5")
	//		task = 5;
	//	else if (key == "-t6")
	//		task = 6;
	//	else
	//		break;
	//}


	for (int i = 1; i < argc; i += 2) {
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

	//graph.readGraphMatrix("C:/Users/nurie/source/repos/graphs/task6/matrix_t6_001.txt");

	/*switch (task)
	{
	case 1:
		exercise1(graph);
		break;
	case 2:
		exercise2(graph);
		break;
	case 3:
		exercise3(graph);
		break;
	case 4:
		exercise4(graph, argc, argv);
		break;
	case 5:
		exercise5(graph, argc, argv);
		break;
	case 6:
		exercise6(graph, argc, argv);
		break;
	default:
		break;
	}*/
	exercise4(graph, argc, argv);
}