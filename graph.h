#pragma once
#include <iostream>
#include <fstream>

class graph {
	struct vertex {
	public:
		int number;
		vertex(int num) {
			number = num;
		};
	};

public:
	int n = 0;
	int** adjancency_matrix = nullptr;
	bool is_created = false;
	void readGraphEdges(const char* url);
	void readGraphMatrix(const char* url);
	bool isCreated();
	int weight(vertex vi, vertex vj);
	bool isEdge(vertex vi, vertex vj);
	void printAdjancencyMatrix();
	void printAdjancencyList(vertex v);
	void printListOfEdges();
	void printListOfEdges(vertex v);
	bool isDirected();
};