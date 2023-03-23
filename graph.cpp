#include "graph.h"

graph::graph() 
{
	std::cout << "Input the number of vertex: ";
	std::cin >> n;
	adjancency_matrix = new int* [n];
	for (int i = 0; i < n; i++) adjancency_matrix[i] = new int[n];
}

graph::graph(char* url) 
{
	char* str = new char[1024];
	n = 0;
	std::ifstream file(url);
	while (!file.eof())
	{
		file.getline(str, 1024, '\n');
		n++;
	}
	file.close();
	delete str;
	adjancency_matrix = new int* [n];
	for (int i = 0; i < n; i++) adjancency_matrix[i] = new int[n];
	file.open(url);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			file >> adjancency_matrix[i][j];
		}
	file.close();
	is_created = true;
}

bool graph::check_creation() 
{
	if (is_created == false) {
		std::cout << "Graph is not created!!\n";
		return false;
	}
	else return true;
}

int graph::weight(vertex vi, vertex vj) 
{
	bool check = check_creation();
	if (check == false) return -1;
	return adjancency_matrix[vi.number - 1][vj.number - 1];
}

bool graph::is_edge(vertex vi, vertex vj) 
{
	if (adjancency_matrix[vi.number - 1][vj.number - 1] != 0) return true;
	else return false;
}

void graph::print_adjancency_matrix() 
{
	check_creation();
	std::cout << "	Adjancency matrix:\n";
	for (int i = 0; i < n; i++) {
		std::cout << "\t";
		for (int j = 0; j < n; j++)
			std::cout << adjancency_matrix[i][j] << "\t";
		std::cout << "\n";
	}
}

void graph::print_adjancency_list(vertex v) {
	std::cout << "List of ajancency vertex for vertex number " << v.number << ": ";
	for (int j = 0; j < n; j++) {
		if (adjancency_matrix[v.number - 1][j] != 0) std::cout << j + 1 << ", ";
	}
}
