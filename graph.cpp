#include "graph.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>

#define INF 999

void Graph::readGraphMatrix(std::string url)
{
	std::ifstream file(url);
	std::string unused;
	while (std::getline(file, unused)) ++number_of_vertex;
	file.close();
	adjancency_matrix = new int*[number_of_vertex];
	for (int i = 0; i < number_of_vertex; i++)
		adjancency_matrix[i] = new int[number_of_vertex];
	file.open(url);
	for (int i = 0; i < number_of_vertex; i++)
		for (int j = 0; j < number_of_vertex; j++)
			file >> adjancency_matrix[i][j];
	file.close();
}

void Graph::readGraphAdjacency(std::string url)
{
	std::ifstream file(url);
	if (!file.is_open())
	{
		std::cout << "Error! File is not open!\n";
		return;
	}
	std::string str;
	while (std::getline(file, str)) ++number_of_vertex;
	file.close();
	adjancency_matrix = new int* [number_of_vertex];
	file.open(url);
	int counter = 0;
	int c;
	while (std::getline(file, str))
	{
		std::istringstream iss(str);
		while (iss >> c)
			adjancency_matrix[counter][c - 1] = 1;
		counter++;
	}
	file.close();
	
}

void Graph::readGraphEdges(std::string url)
{
	std::ifstream file(url);
	if (!file.is_open())
	{
		std::cout << "Error! File is not open!\n";
		return;
	}
	std::string str;
	while (!file.eof())
	{
		getline(file, str);
	}
	auto it = std::find_if(str.begin(), str.end(), isdigit);
	if (it != str.end())
		number_of_vertex = std::atoi(str.c_str() + (it - str.begin()));
	adjancency_matrix = new int* [number_of_vertex];
	for (int i = 0; i < number_of_vertex; i++)
		adjancency_matrix[i] = new int[number_of_vertex];
	for (int i = 0; i < number_of_vertex; i++)
		for (int j = 0; j < number_of_vertex; j++)
			adjancency_matrix[i][j] = 0;
	int a = 0, b = 0, r = 0;
	file.close();
	file.open(url);
	while (!file.eof())
	{
		file >> a >> b >> r;
		adjancency_matrix[a - 1][b - 1] = r;
	}
	file.close();
}

bool Graph::isCreated() 
{
	if (is_created == false) {
		std::cout << "Graph is not created!!\number_of_vertex";
		return false;
	}
	else return true;
}

int Graph::weight(vertex vi, vertex vj) 
{
	bool check = isCreated();
	if (check == false) return -1;
	return adjancency_matrix[vi.number - 1][vj.number - 1];
}

bool Graph::isEdge(vertex vi, vertex vj) 
{
	if (adjancency_matrix[vi.number - 1][vj.number - 1] != 0) return true;
	else return false;
}

void Graph::printAdjancencyMatrix() 
{
	if (isCreated())
	{
		std::cout << "	Adjancency matrix:\number_of_vertex";
		for (int i = 0; i < number_of_vertex; i++) 
		{
			std::cout << "\t";
			for (int j = 0; j < number_of_vertex; j++)
				std::cout << adjancency_matrix[i][j] << "\t";
			std::cout << "\number_of_vertex";
		}
	}
	else isCreated();
}

void Graph::printAdjancencyList(vertex v) 
{
	std::cout << "List of ajancency vertex for vertex number " << v.number << ": ";
	for (int j = 0; j < number_of_vertex; j++) 
	{
		if (adjancency_matrix[v.number - 1][j] != 0) std::cout << j + 1 << ", ";
	}
}

bool Graph::isDirected() 
{
	bool yes = false;
	for (int i = 0; i < number_of_vertex; i++)
		for (int j = i+1; j < number_of_vertex; j++) 
		{
			if (adjancency_matrix[i][j] != adjancency_matrix[j][i]) 
			{
				yes = true;
				return yes;
			}
		}
	return yes;
}

bool Graph::bfs(int v) {
	visited = new bool[number_of_vertex];
	for (int i = 0; i < number_of_vertex; i++)
		visited[i] = false;
	std::queue<int> q;
	visited[v] = true;
	q.push(v);
	while (!q.empty())
	{
		int s = q.front();
		visited[s] = true;
		q.pop();
		for (int i = 0; i < number_of_vertex; i++)
			if (adjancency_matrix[s][i] != 0)
				q.push(i);
	}
	for (int i = 0; i < number_of_vertex; i++)
		if (visited[i] == false)
		{
			return false;
		}
	return true;
}

std::pair<int, int*> Graph::bfsA()
{
	std::pair<int, int*> pair;
	int cnt = 0;
	std::queue<int> q;
	int* cmpnt = new int[number_of_vertex];
	for (int i = 0; i < number_of_vertex; i++)
		cmpnt[i] = -1;
	for (int i = 0; i < number_of_vertex; i++)
	{
		if (cmpnt[i] != -1)
			continue;
		q.push(i);
		while (!q.empty())
		{
			int v = q.front();
			q.pop();
			if (cmpnt[i] != -1)
				continue;
			cmpnt[v] = cnt;
			for (int j = 0; j < number_of_vertex; j++)
				if (adjancency_matrix[i][j] != 0 && cmpnt[j] == -1)
					q.push(j);
		}
		cnt++;
	}
	pair.first = cnt;
	pair.second = cmpnt;
	return pair;
}


// Дописать две функции printListOfEdges();