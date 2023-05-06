#include "graph.h"
#include <vector>
#include "exercise3.h"
#include <list>

std::vector<char> used;
int ch;
std::vector<int> h, d;


void dfsA(Graph graph, int v, int p = -1)
{
	int num_of_vert = graph.number_of_vertex;
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
				std::cout << v << "-" << to << " - мост\n";	// ребро (v, to) - мост
		}
	}
}



void dfsB(Graph graph,int v, int p = -1)
{
	int num_of_vert = graph.number_of_vertex;
	used[v] = true;
	d[v] = h[v] = (p == -1 ? 0 : h[p] + 1);
	int child = 0;
	for (int i = 0; i < num_of_vert; i++)
	{
		int to = graph.adjancency_matrix[v][i];
		if (to == p)
			continue;
		if (used[to])
			d[v] = std::min(d[v], h[to]);
		else
		{
			dfsB(graph, to, v);
			d[v] = std::min(d[v], d[to]);
			if (d[to] >= h[v] && p != -1)
				std::cout << v << " - точка сочленения\n";
			++child;
		}

	}
	if (p == -1 && child > 1)
		std::cout << v << " - точка сочленения\n";
}

void exercise3(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;
	for (int i = 0; i < num_of_vert; i++)
		for (int j = 0; j < num_of_vert; j++)
			if (graph.adjancency_matrix[i][j] == 1)
				graph.adjancency_matrix[i][j] = -1;
	h.resize(num_of_vert);
	d.resize(num_of_vert);
	used.resize(num_of_vert);
	for (int i = 0; i < num_of_vert; i++)
	{
		used[i] = false;
		h[i] = 0;
		d[i] = 0;
	}
	dfsA(graph, 0);

	for (int i = 0; i < num_of_vert; i++)
	{
		used[i] = false;
		h[i] = 0;
		d[i] = 0;
	}
	dfsB(graph, 0);
	return;
}