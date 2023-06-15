#include "exercise4.h"
#include "exercise3.h"
#include "graph.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>

struct Edge
{
	int src;
	int dest;
	int weight;
	bool operator<(Edge& other)
	{
		return weight < other.weight;
	}
};

int findRoot(std::vector<int>& parent, int v)
{
	if (parent[v] == -1)
		return v;
	return findRoot(parent, parent[v]);
}

void unionSets(std::vector<int>& parent, int root1, int root2)
{
	parent[root1] = root2;
}

int find(std::vector<int>& parent, int i) {
	if (parent[i] == i)
		return i;
	return find(parent, parent[i]);
}

void unionComp(std::vector<int>& parent, std::vector<int>& rank, int x, int y) {
	int xroot = find(parent, x);
	int yroot = find(parent, y);

	if (rank[xroot] < rank[yroot])
		parent[xroot] = yroot;
	else if (rank[xroot] > rank[yroot])
		parent[yroot] = xroot;
	else {
		parent[yroot] = xroot;
		rank[xroot]++;
	}
}

int findMinKeyVertex(std::vector<int>& key, std::vector<bool>& mst_vector, int num_of_vert)
{
	int min_key = INT_MAX;
	int min_key_vertex = -1;

	for (int i = 0; i < num_of_vert; ++i)
		if (!mst_vector[i] && key[i] < min_key)
		{
			min_key = key[i];
			min_key_vertex = i;
		} // end if

	return min_key_vertex;
} // end findMinKeyVertex()

//************************Алгоритм Борувки**********************************

void findMSTBr(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	std::vector<Edge> mstTree;

	while (mstTree.size() < num_of_vert - 1) 
	{
		std::vector<int> parent(num_of_vert);
		std::vector<int> rank(num_of_vert);

		for (int v = 0; v < num_of_vert; ++v) 
		{
			parent[v] = v;
			rank[v] = 0;
		}

		for (int comp = 0; comp < num_of_vert; ++comp) 
		{
			int minWeight = INT_MAX;
			int minSrc = -1;
			int minDest = -1;

			for (int src = 0; src < num_of_vert; ++src) {
				for (int dest = 0; dest < num_of_vert; ++dest)
				{
					if (graph.adjancency_matrix[src][dest] != 0)
					{
						int srcComp = find(parent, src);
						int destComp = find(parent, dest);

						if (srcComp != destComp && graph.adjancency_matrix[src][dest] < minWeight) 
						{
							minWeight = graph.adjancency_matrix[src][dest];
							minSrc = src;
							minDest = dest;
						}
					}
				}
			}

			if (minSrc != -1 && minDest != -1) 
			{
				mstTree.push_back({ minSrc, minDest, minWeight });
				unionComp(parent, rank, minSrc, minDest);
			}
		}
	}

	int total_weight = 0;

	for (const auto& edge : mstTree)
		total_weight += edge.weight;

	std::cout << "Остовное дерево:\n";
	for (const auto& edge : mstTree)
		std::cout << edge.src+1 << "-" << edge.dest+1 << "(" << edge.weight << ")\n";

	std::cout << "Суммарный вес остовного дерева: " << total_weight;
}


void findMSTBr(std::vector<std::vector<int>> graph, int num_of_vert)
{
	std::vector<Edge> mstTree;

	while (mstTree.size() < num_of_vert - 1) 
	{
		std::vector<int> parent(num_of_vert);
		std::vector<int> rank(num_of_vert);

		for (int v = 0; v < num_of_vert; ++v) 
		{
			parent[v] = v;
			rank[v] = 0;
		}

		for (int comp = 0; comp < num_of_vert; ++comp) 
		{
			int minWeight = INT_MAX;
			int minSrc = -1, minDest = -1;

			for (int src = 0; src < num_of_vert; ++src) 
			{
				for (int dest = 0; dest < num_of_vert; ++dest) 
				{
					if (graph[src][dest] != 0) {
						int srcComp = find(parent, src);
						int destComp = find(parent, dest);

						if (srcComp != destComp && graph[src][dest] < minWeight) 
						{
							minWeight = graph[src][dest];
							minSrc = src;
							minDest = dest;
						}
					}
				}
			}

			if (minSrc != -1 && minDest != -1) 
			{
				mstTree.push_back({ minSrc, minDest, minWeight });
				unionComp(parent, rank, minSrc, minDest);
			}
		}
	}

	int total_weight = 0;

	for (const auto& edge : mstTree)
		total_weight += edge.weight;

	std::cout << "Остовное дерево:\n";
	for (const auto& edge : mstTree)
		std::cout << edge.src + 1 << "-" << edge.dest + 1 << "(" << edge.weight << ")\n";

	std::cout << "Суммарный вес остовного дерева: " << total_weight;
}





//**************************Алгоритм Крускала********************************

void findMSTKr(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	std::vector<Edge> mstEdges;

	std::vector<int> parent(num_of_vert, -1);

	int total_weight = 0;
	int edge_counter = 0;

	// перенос ребер в mst 
	for (int i = 0; i <num_of_vert;++i)
		for (int j = 0; j < num_of_vert; ++j)
			if (graph.adjancency_matrix[i][j])
			{
				Edge edge;
				edge.src = i;
				edge.dest = j;
				edge.weight = graph.adjancency_matrix[i][j];
				mstEdges.push_back(edge);
			}

	std::sort(mstEdges.begin(), mstEdges.end(), [](const Edge& a, const Edge& b) {return a.weight < b.weight; });

	for (Edge& edge : mstEdges)
	{
		int root1 = findRoot(parent, edge.src);
		int root2 = findRoot(parent, edge.dest);

		if (root1 != root2)
		{
			mstEdges[edge_counter++] = edge;
			total_weight += edge.weight;

			unionSets(parent, root1, root2);
		}
		if (edge_counter == num_of_vert - 1)
			break;
	}

	std::cout << "Остовное дерево:\n";
	for (int i = 0; i < num_of_vert; ++i)
		std::cout << mstEdges[i].src+1 << "-" << mstEdges[i].dest+1 << "(" << mstEdges[i].weight << ")\n";

	std::cout << "Суммарный вес остовного дерева: " << total_weight;
}

void findMSTKr(std::vector<std::vector<int>>& undirGraph, int num_of_vert)
{
	std::vector<Edge> mstEdges;

	std::vector<int> parent(num_of_vert, -1);

	int total_weight = 0;
	int edge_counter = 0;

	for (int i = 0; i < num_of_vert; ++i)
		for (int j = 0; j < num_of_vert; ++j)
			if (undirGraph[i][j])
			{
				Edge edge;
				edge.src = i;
				edge.dest = j;
				edge.weight = undirGraph[i][j];
				mstEdges.push_back(edge);
			}

	std::sort(mstEdges.begin(), mstEdges.end());

	for (Edge& edge : mstEdges)
	{
		int root1 = findRoot(parent, edge.src);
		int root2 = findRoot(parent, edge.dest);

		if (root1 != root2)
		{
			mstEdges[edge_counter++] = edge;
			total_weight += edge.weight;

			unionSets(parent, root1, root2);
		}
		if (edge_counter == num_of_vert - 1)
			break;
	}

	std::cout << "Остовное дерево:\n";
	for (int i = 0; i < num_of_vert; ++i)
		std::cout << mstEdges[i].src+1 << "-" << mstEdges[i].dest+1 << "(" << mstEdges[i].weight << ")\n";

	std::cout << "Суммарный вес остовного дерева: " << total_weight;
}



// **************************АЛГОРИТМ ПРИМА***************************

void findMSTPr(Graph graph)
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
	std::cout << "Остовное дерево:\n";
	for (int i = 1; i < parent.size(); ++i)
		std::cout << parent[i] + 1 << "-" << i + 1 << " (" << graph.adjancency_matrix[i][parent[i]] << ")\n";

	// Вычисление суммарного веса остовного дерева
	int total_weight = 0;
	for (int i = 1; i < num_of_vert; ++i)
		total_weight += graph.adjancency_matrix[i][parent[i]];

	std::cout << "Суммарный вес остовного дерева: " << total_weight;
} // end findMST()

void findMSTPr(std::vector<std::vector<int>>& undirGraph, int num_of_vert)
{
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
	std::cout << "Остовное дерево:\n";
	for (int i = 1; i < parent.size(); ++i)
		std::cout << parent[i] << "-" << i << " (" << undirGraph[i][parent[i]] << ")\n";

	// Вычисление суммарного веса остовного дерева
	int total_weight = 0;
	for (int i = 1; i < num_of_vert; ++i)
		total_weight += undirGraph[i][parent[i]];

	std::cout << "Суммарный вес остовного дерева: " << total_weight;
} // end findMST()

void exercise4(Graph graph, int argc, const char* argv[])
{
	int algorithm = 0;

	for (int i = 0; i < argc; ++i)
	{
		std::string key = argv[i];
		if (key == "-k") 
		{
			algorithm = 1;
			break;
		}
		else if (key == "-p") 
		{
			algorithm = 2;
			break;
		}
		else if (key == "-b") 
		{
			algorithm = 3;
			break;
		}
		else if (key == "-s")
		{
			algorithm = 4;
			break;
		}
	}

	int timek, timep, timeb;

	if (!graph.isDirected())
	{
		if (algorithm == 1)
			findMSTKr(graph);
		if (algorithm == 2)
			findMSTPr(graph);
		if (algorithm == 3)
			findMSTBr(graph);
		if (algorithm == 4)
		{
			std::cout << "Kruskala\n";
			findMSTKr(graph);
			std::cout << "\n\nPrima\n";
			findMSTPr(graph);
			std::cout << "\n\nBoruvka\n";
			findMSTBr(graph);
		}
	}
	else
	{
		std::vector<std::vector<int>> 
			undirGraph = convertToUndirectedGraph(graph);
		if (algorithm == 1)
			findMSTKr(undirGraph, graph.number_of_vertex);
		if (algorithm == 2)
			findMSTPr(undirGraph, graph.number_of_vertex);
		if (algorithm == 3)
			findMSTBr(undirGraph, graph.number_of_vertex);
		if (algorithm == 4)
		{
			std::cout << "Kruskala\n";
			timek = clock();
			findMSTKr(undirGraph, graph.number_of_vertex);
			timek = clock() - timek;
			std::cout << "\n\nPrima\n";
			timep = clock();
			findMSTPr(undirGraph, graph.number_of_vertex);
			timep = clock() - timep;
			std::cout << "\n\nBoruvka\n";
			timeb = clock();
			findMSTBr(undirGraph,graph.number_of_vertex);
			timeb = clock() - timeb;
			std::cout << "\nВремя работы алгоритма Крускала " << timek;
			std::cout << "\nВремя работы алгоритма Прима " << timep;
			std::cout << "\nВремя работы алгоритма Борувки " << timeb;
		}
	}
}