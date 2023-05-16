#include "graph.h"
#include <vector>
#include "exercise3.h"
#include <list>
#include <iostream>

#define MIN(a,b) a < b ? a : b

void dfs(Graph graph, int v, int parent, std::vector<int>& disc, std::vector<int>& low, std::vector<bool>& visited, std::vector<bool>& articularPoints, std::vector<std::pair<int, int>>& bridges, int& time)
{
	int num_of_vert = graph.number_of_vertex;
	visited[v] = true;
	disc[v] = low[v] = ++time;
	int childCounter = 0;

	for (int i = 0; i < num_of_vert; ++i)
	{
		if (graph.adjancency_matrix[v][i])
			if (!visited[i])
			{
				childCounter++;
				dfs(graph, i, v, disc, low, visited, articularPoints, bridges, time);
				low[v] = MIN(low[v], low[i]);

				if (parent != -1 && low[i] >= disc[v])
					articularPoints[v] = true;

				if (low[i] > disc[v])
					bridges.push_back({ v, i });
			}
			else if (i != parent)
				low[v] = MIN(low[v], disc[i]);
	}

	if (parent == -1 && childCounter > 1)
		articularPoints[v] = true;
}

void dfs(std::vector<std::vector<int>> graph, int v, int parent, std::vector<int>& disc, std::vector<int>& low, std::vector<bool>& visited, std::vector<bool>& articularPoints, std::vector<std::pair<int, int>>& bridges, int& time)
{
	int num_of_vert = graph.size();
	visited[v] = true;
	disc[v] = low[v] = ++time;
	int childCounter = 0;

	for (int i = 0; i < num_of_vert; ++i)
	{
		if (graph[v][i])
			if (!visited[i])
			{
				childCounter++;
				dfs(graph, i, v, disc, low, visited, articularPoints, bridges, time);
				low[v] = MIN(low[v], low[i]);

				if (parent != -1 && low[i] >= disc[v])
					articularPoints[v] = true;

				if (low[i] > disc[v])
					bridges.push_back({ v, i });
			}
			else if (i != parent)
				low[v] = MIN(low[v], disc[i]);
	}

	if (parent == -1 && childCounter > 1)
		articularPoints[v] = true;
}

void findBridgesAndArticulationPoints(Graph graph, std::vector<bool>& articulationPoints, std::vector<std::pair<int, int>>& bridges)
{
	int num_of_vert = graph.number_of_vertex;
	std::vector<int> disc(num_of_vert, 0);
	std::vector<int> low(num_of_vert, 0);
	std::vector<bool> visited(num_of_vert, false);
	int time = 0;

	for (int i = 0; i < num_of_vert; ++i)
		if (!visited[i])
			dfs(graph, i, -1, disc, low, visited, articulationPoints, bridges, time);
}

void findBridgesAndArticulationPoints(std::vector<std::vector<int>> graph, std::vector<bool>& articulationPoints, std::vector<std::pair<int, int>>& bridges)
{
	int num_of_vert = graph.size();
	std::vector<int> disc(num_of_vert, 0);
	std::vector<int> low(num_of_vert, 0);
	std::vector<bool> visited(num_of_vert, false);
	int time = 0;

	for (int i = 0; i < num_of_vert; ++i)
		if (!visited[i])
			dfs(graph, i, -1, disc, low, visited, articulationPoints, bridges, time);
}

std::vector<std::vector<int>> convertToUndirectedGraph(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;
	std::vector<std::vector<int>> undirGraph(num_of_vert, std::vector<int>(num_of_vert, 0));
	for (int i = 0; i < num_of_vert; ++i)
		for (int j = 0; j < num_of_vert; ++j)
			if (graph.adjancency_matrix[i][j])
				undirGraph[i][j] = undirGraph[j][i] = 1;

	return undirGraph;
}

void exercise3(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	std::vector<bool> articulationPoints(num_of_vert, false);
	std::vector<std::pair<int, int>> bridges;
	
	if (graph.isDirected())
	{
		std::vector<std::vector<int>> undirGraph = convertToUndirectedGraph(graph);
		findBridgesAndArticulationPoints(undirGraph, articulationPoints, bridges);
	}
	else
		findBridgesAndArticulationPoints(graph, articulationPoints, bridges);


	std::cout << "Шарниры в графе:\n";
	for (int i = 0; i < num_of_vert; ++i)
		if (articulationPoints[i])
			std::cout << i + 1 << " ";
	
	std::cout << "\nМосты в графе:\n";
	for (const auto& bridge : bridges)
		std::cout << bridge.first+1 << "-" << bridge.second+1 << std::endl;
}