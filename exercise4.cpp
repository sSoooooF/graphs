#include "exercise4.h"
#include "exercise3.h"
#include "graph.h"
#include <vector>
#include <iostream>
#include <algorithm>

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

// ����� ������� ������� � ����������� ������, ������� ��� �� �������� � �������� ������
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

//************************�������� �������**********************************

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

	std::cout << "�������� ������:\n";
	for (const auto& edge : mstEdges)
		std::cout << edge.src+1 << "-" << edge.dest+1 << "(" << edge.weight << ")\n";

	std::cout << "��������� ��� ��������� ������: " << total_weight;
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

	std::cout << "�������� ������:\n";
	for (const auto& edge : mstEdges)
		std::cout << edge.src+1 << "-" << edge.dest+1 << "(" << edge.weight << ")\n";

	std::cout << "��������� ��� ��������� ������: " << total_weight;
}




//**************************�������� ��������********************************

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

	std::cout << "�������� ������:\n";
	for (int i = 0; i < num_of_vert; ++i)
		std::cout << mstEdges[i].src+1 << "-" << mstEdges[i].dest+1 << "(" << mstEdges[i].weight << ")\n";

	std::cout << "��������� ��� ��������� ������: " << total_weight;
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

	std::cout << "�������� ������:\n";
	for (int i = 0; i < num_of_vert; ++i)
		std::cout << mstEdges[i].src+1 << "-" << mstEdges[i].dest+1 << "(" << mstEdges[i].weight << ")\n";

	std::cout << "��������� ��� ��������� ������: " << total_weight;
}



// **************************�������� �����***************************

void findMSTPr(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	// �������� �������� ������ ��������� � �������� ������
	std::vector<int> parent(num_of_vert, -1);

	// �������� ���� �����
	std::vector<int> key(num_of_vert, INT_MAX);

	// ������������ ������, ������� ��� �������� � �������� ������
	std::vector<bool> mstVector(num_of_vert, false);

	key[0] = 0; // ���� ������ ������� = 0
	parent[0] = -1; // ������ ������� �� ����� ��������

	// ����� ��������� ������
	for (int i = 0; i < num_of_vert - 1; ++i)
	{
		int u = findMinKeyVertex(key, mstVector, num_of_vert);
		mstVector[u] = true;

		// ��������� ����� � ��������� ������� ������
		for (int j= 0;j<num_of_vert;++j)
			if (graph.adjancency_matrix[u][j] && !mstVector[j] && graph.adjancency_matrix[u][j] < key[j])
			{
				parent[j] = u;
				key[j] = graph.adjancency_matrix[u][j];
			} // end if
	} // end for

	// ����� ��������� ������
	std::cout << "�������� ������:\n";
	for (int i = 1; i < parent.size(); ++i)
		std::cout << parent[i] + 1 << "-" << i + 1 << " (" << graph.adjancency_matrix[i][parent[i]] << ")\n";

	// ���������� ���������� ���� ��������� ������
	int total_weight = 0;
	for (int i = 1; i < num_of_vert; ++i)
		total_weight += graph.adjancency_matrix[i][parent[i]];

	std::cout << "��������� ��� ��������� ������: " << total_weight;
} // end findMST()

void findMSTPr(std::vector<std::vector<int>>& undirGraph, int num_of_vert)
{
	// �������� �������� ������ ��������� � �������� ������
	std::vector<int> parent(num_of_vert, -1);

	// �������� ���� �����
	std::vector<int> key(num_of_vert, INT_MAX);

	// ������������ ������, ������� ��� �������� � �������� ������
	std::vector<bool> mstVector(num_of_vert, false);

	key[0] = 0; // ���� ������ ������� = 0
	parent[0] = -1; // ������ ������� �� ����� ��������

	// ����� ��������� ������
	for (int i = 0; i < num_of_vert - 1; ++i)
	{
		int u = findMinKeyVertex(key, mstVector, num_of_vert);
		mstVector[u] = true;

		// ��������� ����� � ��������� ������� ������
		for (int j = 0; j < num_of_vert; ++j)
			if (undirGraph[u][j] && !mstVector[j] && undirGraph[u][j] < key[j])
			{
				parent[j] = u;
				key[j] = undirGraph[u][j];
			} // end if
	} // end for

	// ����� ��������� ������
	std::cout << "�������� ������:\n";
	for (int i = 1; i < parent.size(); ++i)
		std::cout << parent[i] << "-" << i << " (" << undirGraph[i][parent[i]] << ")\n";

	// ���������� ���������� ���� ��������� ������
	int total_weight = 0;
	for (int i = 1; i < num_of_vert; ++i)
		total_weight += undirGraph[i][parent[i]];

	std::cout << "��������� ��� ��������� ������: " << total_weight;
} // end findMST()

void exercise4(Graph graph)
{
	if (!graph.isDirected())
		findMSTBr(graph);
	else
	{
		std::vector<std::vector<int>> undirGraph = convertToUndirectedGraph(graph);
		findMSTBr(undirGraph, graph.number_of_vertex);
	}
}