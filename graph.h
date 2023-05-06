#pragma once
#include <iostream>
#include <fstream>

class Graph {
public:
	int number_of_vertex = 0;		// количество вершин в графе
	int** adjancency_matrix = nullptr;	// матрица инцидентности
	bool is_created = false;			// создан ли граф
	bool* visited;						// посещенные вершины
	void readGraphEdges(std::string url);	// чтение графа из файла с ребрами
	void readGraphMatrix(std::string url);	// чтение графа из матрицы
	void readGraphAdjacency(std::string url);	// чтение графа из списка смежности
	bool isCreated();	// создан ли граф?
	int weight(int vi, int vj);	// возвращает вес ребра
	bool isEdge(int vi, int vj);	// есть ли ребро между vi и vj
	void printAdjancencyMatrix();	// вывод матрицы смежности
	void printAdjancencyList(int v);	// вывод списка смжености ля вершины v
	void printListOfEdges();	// вывод списка ребер
	void printListOfEdges(int v);	// вывод списка ребер вершины v
	bool isDirected();			// граф ориентированный?
}; // class Graph