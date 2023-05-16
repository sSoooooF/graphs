#include "graph.h"
#include <queue>
#include <vector>
#include <stack>
#include "exercise2.h"

#define MAX(a,b) a >= b ? a : b

bool isGraphConnected(Graph graph, int v)
{
	int num_of_vert = graph.number_of_vertex;

	std::vector<bool> visited(num_of_vert, false);
	visited[v] = true;

	std::queue<int> q;
	q.push(v);

	while (!q.empty())
	{
		int s = q.front();
		q.pop();

		for (int i = 0 ; i < num_of_vert; ++i)
			if (graph.adjancency_matrix[s][i] && !visited[i])
			{
				visited[i] = true;
				q.push(i);
			}
	}
	for (bool visitedVertex : visited)
		if (!visitedVertex)
			return false;

	return true;
}

void bfs(Graph graph, int v, std::vector<bool>& visited, std::vector<int>& component)
{
	int num_of_vert = graph.number_of_vertex;
	std::queue<int> q;
	q.push(v);
	visited[v] = true;
	component.push_back(v);

	while (!q.empty())
	{
		int s = q.front();
		q.pop();

		for (int  i = 0 ; i < num_of_vert;++i)
			if (graph.adjancency_matrix[s][i] && !visited[i])
			{
				visited[i] = true;
				q.push(i);
				component.push_back(i);
			}
	}
}

std::vector<std::vector<int>> findConnectedComponents(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;
	std::vector<bool> visited(num_of_vert, false);
	std::vector<std::vector<int>> components;

	for (int i = 0; i < num_of_vert; ++i)
	{
		if (!visited[i])
		{
			std::vector<int> component;
			bfs(graph, i, visited, component);
			components.push_back(component);
		}
	}

	return components;
}

void dfs(Graph graph, int v, std::vector<bool>& visited, std::stack<int>& stk)
{
	visited[v] = true;
	int num_of_vert = graph.number_of_vertex;

	for (int i = 0; i < num_of_vert; ++i)
		if (graph.adjancency_matrix[v][i] && !visited[i])
			dfs(graph, i, visited, stk);

	stk.push(v);
}

void dfsTranspose(std::vector<std::vector<int>> transposeGraph, int v, std::vector<bool>& visited, std::vector<int>& component)
{
	visited[v] = true;
	component.push_back(v);

	for (int i = 0; i < transposeGraph.size(); ++i)
		if (transposeGraph[v][i] && !visited[i])
			dfsTranspose(transposeGraph, i, visited, component);
}

void dfsTranspose(std::vector<std::vector<int>> transposeGraph, int v, std::vector<bool>& visited)
{
	visited[v] = true;

	for (int i = 0; i < transposeGraph.size(); ++i)
		if (transposeGraph[v][i] && !visited[i])
			dfsTranspose(transposeGraph, i, visited);
}

bool isDigraphWeaklyConnected(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	for (int i = 0; i < num_of_vert; ++i)
	{
		std::vector<bool> visited(num_of_vert, false);
		std::stack<int> stk;
		dfs(graph, i, visited,stk);
		for (bool visitedVertex : visited)
			if (!visitedVertex)
				return false;
	}

	return true;
}

bool isDigraphStronglyConnected(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	std::vector<bool> visited(num_of_vert, false);
	std::stack<int> stk;
	dfs(graph, 0, visited,stk);

	for (bool visitedVertex : visited)
		if (!visitedVertex)
			return false;

	std::vector<std::vector<int>> transposeGraph(num_of_vert, std::vector<int>(num_of_vert));
	for (int i = 0; i < num_of_vert; ++i)
		for (int j = 0; i < num_of_vert; ++i)
			transposeGraph[j][i] = graph.adjancency_matrix[i][j];

	visited.assign(num_of_vert, false);
	dfsTranspose(transposeGraph, 0, visited);

	for (bool visitedVertex : visited)
		if (!visitedVertex)
			return false;

	return true;
}

std::vector<std::vector<int>> findStronglyConnectedComponents(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	std::vector<bool> visited(num_of_vert, false);
	std::stack<int> stk;
	for (int i = 0; i < num_of_vert; ++i)
		if (!visited[i])
			dfs(graph, i, visited, stk);

	std::vector<std::vector<int>> transposeGraph(num_of_vert, std::vector<int>(num_of_vert));
	for (int i = 0; i < num_of_vert; ++i)
		for (int j = 0; i < num_of_vert; ++i)
			transposeGraph[j][i] = graph.adjancency_matrix[i][j];

	std::vector<std::vector<int>> components;
	visited.assign(num_of_vert, false);
	while (!stk.empty())
	{
		int s = stk.top();
		stk.pop();

		if (!visited[s])
		{
			std::vector<int> component;
			dfsTranspose(transposeGraph, s, visited, component);
			components.push_back(component);
		}
	}

	return components;
}

void exercise2(Graph graph)
{
	if (!graph.isDirected())
	{
		if (isGraphConnected(graph, 0))
			std::cout << "Граф связен\n";
		else
			std::cout << "Граф не связен\n";

		std::vector<std::vector<int>> components = findConnectedComponents(graph);

		std::cout << "Компоненты связности:\n";
		for (int i = 0; i < components.size(); ++i)
		{
			std::cout << "Компонента " << i + 1 << ": ";
			for (int j = 0; j < components[i].size(); ++j)
				std::cout << components[i][j]+1 << " ";
			std::cout << "\n";
		}
	}
	else
	{
		if (isDigraphWeaklyConnected(graph))
			std::cout << "Орграф слабо связный\n";
		else if(isDigraphStronglyConnected(graph))
			std::cout << "Орграф сильно связный\n";
		else 
			std::cout << "Орграф несвязный\n";

		std::vector<std::vector<int>> components = findStronglyConnectedComponents(graph);

		std::cout << "Компоненты сильной связности:\n";
		for (const auto& component : components)
		{
			for (int vert : component)
				std::cout << vert + 1 << " ";
			std::cout << "\n";
		}
	}
}