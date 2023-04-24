#include "graph.h"
#include <fstream>
#include <string>

void graph::readGraphEdges(const char* url) 
{
	std::ifstream file(url);
	if (!file.is_open()) 
	{
		throw "Error! File is not open!";
		return;
	}
	int num_of_vertex = 0;
	int trash;
	char* str;
	while (!file.eof())
	{
		file.getline(str, 100);
	}
	if (*(str + 1) != ' ') 
	{
		num_of_vertex = *str;
		num_of_vertex *= 10;
		num_of_vertex += *(str + 1);
	}
	adjancency_matrix = new int* [num_of_vertex];
	for (int i = 0; i < num_of_vertex; i++) 
	{
		adjancency_matrix[i] = new int[num_of_vertex];
	}
	for (int i = 0; i < num_of_vertex; i++)
		for (int j = 0; j < num_of_vertex; j++)
			adjancency_matrix[i][j] = 0;
	int a=0, b=0, r=0;
	file.close();
	file.open(url);
	while (!file.eof()) 
	{
		file >> a >> b >> r;
		adjancency_matrix[a - 1][b - 1] = r;
	}
	file.close();
}

void graph::readGraphMatrix(const char* url)
{
	std::ifstream file(url);
	std::string unused;
	while (std::getline(file, unused)) ++n;
	file.close();
	file.open(url);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			file >> adjancency_matrix[i][j];
	file.close();
}

bool graph::isCreated() 
{
	if (is_created == false) {
		std::cout << "Graph is not created!!\n";
		return false;
	}
	else return true;
}

int graph::weight(vertex vi, vertex vj) 
{
	bool check = isCreated();
	if (check == false) return -1;
	return adjancency_matrix[vi.number - 1][vj.number - 1];
}

bool graph::isEdge(vertex vi, vertex vj) 
{
	if (adjancency_matrix[vi.number - 1][vj.number - 1] != 0) return true;
	else return false;
}

void graph::printAdjancencyMatrix() 
{
	isCreated();
	std::cout << "	Adjancency matrix:\n";
	for (int i = 0; i < n; i++) {
		std::cout << "\t";
		for (int j = 0; j < n; j++)
			std::cout << adjancency_matrix[i][j] << "\t";
		std::cout << "\n";
	}
}

void graph::printAdjancencyList(vertex v) 
{
	std::cout << "List of ajancency vertex for vertex number " << v.number << ": ";
	for (int j = 0; j < n; j++) {
		if (adjancency_matrix[v.number - 1][j] != 0) std::cout << j + 1 << ", ";
	}
}

bool graph::isDirected() 
{
	bool yes = false;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (adjancency_matrix[i][j] != adjancency_matrix[i][j]) {
				yes = true;
				return yes;
			}
		}
	return yes;
}

// Дописать две функции printListOfEdges();