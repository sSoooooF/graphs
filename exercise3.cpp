#include "graph.h"
#include <vector>
#include "exercise3.h"
#include <list>
#include <iostream>

#define MIN(a,b) a < b ? a : b

void dfs(Graph graph, int v, int parent, std::vector<int>& time_in, std::vector<int>& up, std::vector<bool>& visited, std::vector<bool>& articularPoints, std::vector<std::pair<int, int>>& bridges, int& time)
{
	int num_of_vert = graph.number_of_vertex;
	visited[v] = true;
	time_in[v] = up[v] = ++time;
	int childCounter = 0;

	for (int i = 0; i < num_of_vert; ++i)
	{
		if (graph.adjancency_matrix[v][i])
			if (!visited[i])
			{
				childCounter++;
				dfs(graph, i, v, time_in, up, visited, articularPoints, bridges, time);
				up[v] = MIN(up[v], up[i]);

				if (parent != -1 && up[i] >= time_in[v])
					articularPoints[v] = true;

				if (up[i] > time_in[v])
					bridges.push_back({ v, i });
			}
			else if (i != parent)
				up[v] = MIN(up[v], time_in[i]);
	}

	if (parent == -1 && childCounter > 1)
		articularPoints[v] = true;
}

void dfs(std::vector<std::vector<int>> graph, int v, int parent, std::vector<int>& time_in, std::vector<int>& up, std::vector<bool>& visited, std::vector<bool>& articularPoints, std::vector<std::pair<int, int>>& bridges, int& time)
{
	int num_of_vert = graph.size();
	visited[v] = true;
	time_in[v] = up[v] = ++time;
	int childCounter = 0;

	for (int i = 0; i < num_of_vert; ++i)
	{
		if (graph[v][i])
			if (!visited[i])
			{
				childCounter++;
				dfs(graph, i, v, time_in, up, visited, articularPoints, bridges, time);
				up[v] = MIN(up[v], up[i]);

				if (parent != -1 && up[i] >= time_in[v])
					articularPoints[v] = true;

				if (up[i] > time_in[v])
					bridges.push_back({ v, i });
			}
			else if (i != parent)
				up[v] = MIN(up[v], time_in[i]);
	}

	if (parent == -1 && childCounter > 1)
		articularPoints[v] = true;
}

void findBridgesAndArticulationPoints(Graph graph, std::vector<bool>& articulationPoints, std::vector<std::pair<int, int>>& bridges)
{
	int num_of_vert = graph.number_of_vertex;
	std::vector<int> time_in(num_of_vert, 0);
	std::vector<int> up(num_of_vert, 0);
	std::vector<bool> visited(num_of_vert, false);
	int time = 0;

	for (int i = 0; i < num_of_vert; ++i)
		if (!visited[i])
			dfs(graph, i, -1, time_in, up, visited, articulationPoints, bridges, time);
}

void findBridgesAndArticulationPoints(std::vector<std::vector<int>> graph, std::vector<bool>& articulationPoints, std::vector<std::pair<int, int>>& bridges)
{
	int num_of_vert = graph.size();
	std::vector<int> time_in(num_of_vert, 0);
	std::vector<int> up(num_of_vert, 0);
	std::vector<bool> visited(num_of_vert, false);
	int time = 0;

	for (int i = 0; i < num_of_vert; ++i)
		if (!visited[i])
			dfs(graph, i, -1, time_in, up, visited, articulationPoints, bridges, time);
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