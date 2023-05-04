#pragma once
#include <iostream>
#include <string>
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
	int** adjancency_matrix = nullptr;
	bool is_created = false;
	bool* visited;
	void readGraphEdges(std::string url);
	void readGraphMatrix(std::string url);
	void readGraphAdjacency(std::string url);
	bool isCreated();
	int weight(vertex vi, vertex vj);
	bool isEdge(vertex vi, vertex vj);
	void printAdjancencyMatrix();
	void printAdjancencyList(vertex v);
	void printListOfEdges();
	void printListOfEdges(vertex v);
	bool isDirected();
	bool bfs(int v);
	std::pair<int,int*> bfsA();


	// excercise 3
	void add(int v);
	void contain(int v);
	void remove(int v);
	void clear();
	void stav(int i);
	int getComponentCount();

}; // class Graph