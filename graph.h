#pragma once
#include <iostream>
#include <fstream>

class Graph {
	struct vertex {
	public:
		int number;
		vertex(int num) {
			number = num;
		}; // vertex()
	}; // struct vertex

public:
	int number_of_vertex = 0;
	int** adjancency_matrix{};
	bool is_created = false;
	void readGraphEdges(const char* url);
	void readGraphMatrix(std::string url);
	bool isCreated();
	int weight(vertex vi, vertex vj);
	bool isEdge(vertex vi, vertex vj);
	void printAdjancencyMatrix();
	void printAdjancencyList(vertex v);
	void printListOfEdges();
	void printListOfEdges(vertex v);
	bool isDirected();
}; // class Graph