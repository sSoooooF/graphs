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

// Поиск индекса вершины с минимальным ключом, которая еще не включена в остовное дерево
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

	std::vector<Edge> mstEdges;

	std::vector<int> cheapest(num_of_vert, INT_MAX);
	std::vector<int> root(num_of_vert);
	std::vector<int> subset(num_of_vert, -1);

	for (int i = 0; i < num_of_vert; ++i)
		root[i] = i;

	int components = num_of_vert;

	int total_weight = 0;

	while (components > 1)
	{
		for (int i = 0; i <num_of_vert;++i)
			for (int j = 0; j < num_of_vert; ++j)
				if (graph.adjancency_matrix[i][j]!=0) {
					int dest = j;

					if (root[i] != root[dest] && graph.adjancency_matrix[i][j] < cheapest[root[i]])
						cheapest[root[i]] = graph.adjancency_matrix[i][j];
				}

		for (int i = 0; i < num_of_vert; ++i)
		{
			int cheapest_edge = cheapest[i];
			if (cheapest_edge != INT_MAX)
			{
				int dest = -1;
				int min_weight = INT_MAX;
				for (int j = 0; j < num_of_vert; ++j)
					if (graph.adjancency_matrix[i][j] != 0)
						if (root[i] != root[j] && graph.adjancency_matrix[i][j] == cheapest_edge)
							if (graph.adjancency_matrix[i][j] < min_weight)
							{
								min_weight = graph.adjancency_matrix[i][j];
								dest = j;
							}

				if (dest != -1)
				{
					mstEdges.push_back({ i, dest, min_weight });
					total_weight += min_weight;

					if (subset[root[i]] < subset[root[dest]])
					{
						root[root[i]] = root[dest];
						subset[root[dest]] += subset[root[i]];
					}
					else {
						root[root[dest]] = root[i];
						subset[root[i]] += subset[root[dest]];
					}
					components--;
				}
				cheapest[i] = INT_MAX;
			}
		}
	}

	std::cout << "Остовное дерево:\n";
	for (const auto& edge : mstEdges)
		std::cout << edge.src+1 << "-" << edge.dest+1 << "(" << edge.weight << ")\n";

	std::cout << "Суммарный вес остовного дерева: " << total_weight;
}


void findMSTBr(std::vector<std::vector<int>> undirGraph,int num_of_vert)
{
	std::vector<Edge> mstEdges;

	std::vector<int> cheapest(num_of_vert, INT_MAX);
	std::vector<int> root(num_of_vert);
	std::vector<int> subset(num_of_vert, -1);

	for (int i = 0; i < num_of_vert; ++i)
		root[i] = i;

	int components = num_of_vert;

	int total_weight = 0;

	while (components > 1)
	{
		for (int i = 0; i < num_of_vert; ++i)
			for (int j = 0; j < num_of_vert; ++j)
				if (undirGraph[i][j] != 0) {
					int dest = j;

					if (root[i] != root[dest] && undirGraph[i][j] < cheapest[root[i]])
						cheapest[root[i]] = undirGraph[i][j];
				}

		for (int i = 0; i < num_of_vert; ++i)
		{
			int cheapest_edge = cheapest[i];
			if (cheapest_edge != INT_MAX)
			{
				int dest = -1;
				int min_weight = INT_MAX;
				for (int j = 0; j < num_of_vert; ++j)
					if (undirGraph[i][j] != 0)
						if (root[i] != root[j] && undirGraph[i][j] == cheapest_edge)
							if (undirGraph[i][j] < min_weight)
							{
								min_weight = undirGraph[i][j];
								dest = j;
							}

				if (dest != -1)
				{
					mstEdges.push_back({ i, dest, min_weight });
					total_weight += min_weight;

					if (subset[root[i]] < subset[root[dest]])
					{
						root[root[i]] = root[dest];
						subset[root[dest]] += subset[root[i]];
					}
					else {
						root[root[dest]] = root[i];
						subset[root[i]] += subset[root[dest]];
					}
					components--;
				}
				cheapest[i] = INT_MAX;
			}
		}
	}

	std::cout << "Остовное дерево:\n";
	for (const auto& edge : mstEdges)
		std::cout << edge.src+1 << "-" << edge.dest+1 << "(" << edge.weight << ")\n";

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

	int time;

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
		std::vector<std::vector<int>> undirGraph = convertToUndirectedGraph(graph);
		if (algorithm == 1)
			findMSTKr(undirGraph, graph.number_of_vertex);
		if (algorithm == 2)
			findMSTPr(undirGraph, graph.number_of_vertex);
		if (algorithm == 3)
			findMSTBr(undirGraph, graph.number_of_vertex);
		if (algorithm == 4)
		{
			std::cout << "Kruskala\n";
			time = clock();
			findMSTKr(undirGraph, graph.number_of_vertex);
			std::cout << "\nВремя работы алгоритма Крускала " << clock()-time << "\n\nPrima\n";
			time = clock();
			findMSTPr(undirGraph, graph.number_of_vertex);
			std::cout << "\nВремя работы алгоритма Прима " << clock() - time << "\n\nBoruvka\n";
			time = clock();
			findMSTBr(undirGraph,graph.number_of_vertex);
			std::cout << "\nВремя работы алгоритма Борувки " << clock() - time;
		}
	}
}