#include "exercise4.h"
#include "exercise3.h"
#include "graph.h"
#include <vector>
#include <iostream>

// Поиск индекса вершины с минимальным ключом, которая еще не включена в остовное дерево
int findMinKeyVertex(std::vector<int>& key, std::vector<bool>& mst_vector, int num_of_vert)
{
	int min_key = INT_MAX;
	int min_key_vertex = -1;

	for (int i = 0; i < num_of_vert;++i)
		if (!mst_vector[i] && key[i] < min_key)
		{
			min_key = key[i];
			min_key_vertex = i;
		} // end if

	return min_key_vertex;
} // end findMinKeyVertex()

// Печать остовного дерева
void printMST(std::vector<int>& parent, Graph graph)
{
	std::cout << "Остовное дерево:\n";
	for (int i = 1; i < parent.size(); ++i)
		std::cout << parent[i] + 1 << "-" << i + 1 << " (" << graph.adjancency_matrix[i][parent[i]] << ")\n";
} // end printMST()

void printMST(std::vector<int>& parent, std::vector<std::vector<int>>& undirGraph)
{
	std::cout << "Остовное дерево:\n";
	for (int i = 1; i < parent.size(); ++i)
		std::cout << parent[i] << "-" << i << " (" << undirGraph[i][parent[i]] << ")\n";
} // end printMST()

int findMST(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	// Хранение индексов вершин родителей в остовном дереве
	std::vector<int> parent(num_of_vert, -1);

	// Хранение веса ребер
	std::vector<int> key(num_of_vert, INT_MAX);

	// Отслеживание вершин, которые уже включены в остовное дерево
	std::vector<bool> mstVector(num_of_vert, false);

	key[0] = 0; // Ключ первой вершины = 0
	parent[0] = -1; // Первая вершина не имеет родителя

	// Поиск оставного дерева
	for (int i = 0; i < num_of_vert - 1; ++i)
	{
		int u = findMinKeyVertex(key, mstVector, num_of_vert);
		mstVector[u] = true;

		// Обновляем ключи и родителей смежных вершин
		for (int j= 0;j<num_of_vert;++j)
			if (graph.adjancency_matrix[u][j] && !mstVector[j] && graph.adjancency_matrix[u][j] < key[j])
			{
				parent[j] = u;
				key[j] = graph.adjancency_matrix[u][j];
			} // end if
	} // end for

	// Вывод остовного дерева
	printMST(parent, graph);

	// Вычисление суммарного веса остовного дерева
	int totalWeight = 0;
	for (int i = 1; i < num_of_vert; ++i)
		totalWeight += graph.adjancency_matrix[i][parent[i]];

	return totalWeight;
} // end findMST()

int findMST(std::vector<std::vector<int>>& undirGraph)
{
	int num_of_vert = undirGraph.size();

	// Хранение индексов вершин родителей в остовном дереве
	std::vector<int> parent(num_of_vert, -1);

	// Хранение веса ребер
	std::vector<int> key(num_of_vert, INT_MAX);

	// Отслеживание вершин, которые уже включены в остовное дерево
	std::vector<bool> mstVector(num_of_vert, false);

	key[0] = 0; // Ключ первой вершины = 0
	parent[0] = -1; // Первая вершина не имеет родителя

	// Поиск оставного дерева
	for (int i = 0; i < num_of_vert - 1; ++i)
	{
		int u = findMinKeyVertex(key, mstVector, num_of_vert);
		mstVector[u] = true;

		// Обновляем ключи и родителей смежных вершин
		for (int j = 0; j < num_of_vert; ++j)
			if (undirGraph[u][j] && !mstVector[j] && undirGraph[u][j] < key[j])
			{
				parent[j] = u;
				key[j] = undirGraph[u][j];
			} // end if
	} // end for

	// Вывод остовного дерева
	printMST(parent, undirGraph);

	// Вычисление суммарного веса остовного дерева
	int total_weight = 0;
	for (int i = 1; i < num_of_vert; ++i)
		total_weight += undirGraph[i][parent[i]];

	return total_weight;
} // end findMST()

void exercise4(Graph graph)
{
	int total_weight;
	if (!graph.isDirected())
		total_weight = findMST(graph);
	else
	{
		std::vector<std::vector<int>> undirGraph = convertToUndirectedGraph(graph);
		total_weight = findMST(undirGraph);
	}
	
	std::cout << "Суммарный вес остовного дерева: " << total_weight;
}