#include "graph.h"
#include <vector>
#include "exercise3.h"

std::vector<char> used;
int ch;
std::vector<int> h, d;

void dfsA(Graph graph, int v, int p = -1)
{
	int num_of_vert = graph.number_of_vertex;
	h.resize(num_of_vert);
	d.resize(num_of_vert);
	used.resize(num_of_vert);
	used[v] = true;
	h[v] = d[v] = ch++;
	for (int i = 0; i < num_of_vert; i++)
	{
		int to = graph.adjancency_matrix[v][i];
		if (to == p) continue;
		if (used[to])	// ребро обратное
			d[v] = std::min(d[v], h[to]);
		else			// ребро прямое
		{
			dfsA(graph, to, v);
			d[v] = std::min(d[v], d[to]);
			if (d[to] > h[v])
				printf("%d - %d - мост", v, to);	// ребро (v, to) - мост
		}
	}
}

int* s;

void dfsB(Graph graph, int v, int p = 0)
{
	int num_of_vert = graph.number_of_vertex;
	d[v] = h[v] = (p == -1 ? 0 : h[p] + 1)

	
}

void exercise3(Graph graph)
{
	int num = graph.number_of_vertex;
	for (int i = 0; i < num; i++)
		for (int j = 0; j < num; j++)
			if (graph.adjancency_matrix[i][j] == 1)
				graph.adjancency_matrix[i][j] = -1;
}