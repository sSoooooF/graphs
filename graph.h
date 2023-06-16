#pragma once
#include <iostream>
#include <fstream>
#include <vector>

struct Edgeloh
{
	int source;
	int desst;
	int weight;
};


class Graph {
public:
	int number_of_vertex = 0;		// ���������� ������ � �����
	int** adjancency_matrix = nullptr;	// ������� �������������
	bool is_created = false;			// ������ �� ����
	void readGraphEdges(std::string url);	// ������ ����� �� ����� � �������
	void readGraphMatrix(std::string url);	// ������ ����� �� �������
	void readGraphAdjacency(std::string url);	// ������ ����� �� ������ ���������
	bool isCreated();	// ������ �� ����?
	int weight(int vi, int vj);	// ���������� ��� �����
	bool isEdge(int vi, int vj);	// ���� �� ����� ����� vi � vj
	void printAdjancencyMatrix();	// ����� ������� ���������
	std::vector<int> printAdjancencyList(int v);	// ����� ������ ��������� �� ������� v
	void printListOfEdges();	// ����� ������ �����
	std::vector<Edgeloh> printListOfEdges(int v);	// ����� ������ ����� ������� v
	bool isDirected();			// ���� ���������������?
}; // class Graph