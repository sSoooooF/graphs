#include "graph.h"
#include <queue>
#include <vector>
#include <stack>
#include "exercise2.h"
#include "exercise4.h"
#include "exercise3.h"

#define MAX(a,b) a >= b ? a : b

bool isGraphConnected(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	std::vector<bool> visited(num_of_vert, false);
	visited[0] = true;

	std::queue<int> q;
	q.push(0);

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

bool isGraphConnected(std::vector<std::vector<int>> graph)
{
	int num_of_vert = graph.size();

	std::vector<bool> visited(num_of_vert, false);
	visited[0] = true;

	std::queue<int> q;
	q.push(0);

	while (!q.empty())
	{
		int s = q.front();
		q.pop();

		for (int i = 0; i < num_of_vert; ++i)
			if (graph[s][i] && !visited[i])
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

bool isStronglyConnected(Graph graph) 
{
	int n = graph.number_of_vertex;

	std::vector<bool> visited(n, false);
	std::queue<int> q;
	q.push(0);
	visited[0] = true;

	while (!q.empty()) 
	{
		int curr = q.front();
		q.pop();

		for (int i = 0; i < n; i++) 
			if (graph.adjancency_matrix[curr][i] != 0 && !visited[i]) 
			{
				q.push(i);
				visited[i] = true;
			}
	}

	for (bool v : visited) 
	{
		if (!v)
			return false;
	}

	for (int i = 0; i < n; i++) 
	{
		visited.assign(n, false);
		q.push(i);
		visited[i] = true;

		while (!q.empty()) {
			int curr = q.front();
			q.pop();

			for (int j = 0; j < n; j++) 
				if (graph.adjancency_matrix[curr][j] != 0 && !visited[j]) 
				{
					q.push(j);
					visited[j] = true;
				}
		}

		for (bool v : visited) 
		{
			if (!v)
				return false;
		}
	}

	return true;
}


bool isWeaklyConnected(Graph graph) 
{
	int n = graph.number_of_vertex;

	std::vector<std::vector<int>> undirectedGraph(n, std::vector<int>(n, 0));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) 
		{
				undirectedGraph[i][j] = 1;
				undirectedGraph[j][i] = 1;
		}

	return isGraphConnected(undirectedGraph);
}

std::vector<std::vector<int>> findConnectedComponents(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;
	std::vector<bool> visited(num_of_vert, false);
	std::vector<std::vector<int>> components;

	for (int i = 0; i < num_of_vert; i++) 
	{
		if (!visited[i]) 
		{
			std::vector<int> component;
			std::queue<int> q;
			q.push(i);
			visited[i] = true;

			while (!q.empty()) 
			{
				int curr = q.front();
				q.pop();
				component.push_back(curr);

				for (int j = 0; j < num_of_vert; j++)
					if (graph.adjancency_matrix[curr][j] != 0 && !visited[j]) 
					{
						q.push(j);
						visited[j] = true;
					}
			}

			components.push_back(component);
		}
	}

	return components;
}

std::vector<std::vector<int>> findConnectedComponents(std::vector<std::vector<int>> graph, int num_of_vert)
{
	std::vector<bool> visited(num_of_vert, false);
	std::vector<std::vector<int>> components;

	for (int i = 0; i < num_of_vert; i++)
	{
		if (!visited[i])
		{
			std::vector<int> component;
			std::queue<int> q;
			q.push(i);
			visited[i] = true;

			while (!q.empty())
			{
				int curr = q.front();
				q.pop();
				component.push_back(curr);

				for (int j = 0; j < num_of_vert; j++)
					if (graph[curr][j] != 0 && !visited[j])
					{
						q.push(j);
						visited[j] = true;
					}
			}

			components.push_back(component);
		}
	}

	return components;
}

void DFS(int v, Graph graph, std::vector<bool>& visited, std::vector<int>& component) 
{
	visited[v] = true;
	component.push_back(v);

	for (int neighbor = 0; neighbor < graph.number_of_vertex; ++neighbor)
		if (graph.adjancency_matrix[v][neighbor] && !visited[neighbor])
			DFS(neighbor, graph, visited, component);
}

void DFS(int v, std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<int>& component) 
{
	visited[v] = true;
	component.push_back(v);

	for (int neighbor = 0; neighbor < graph.size(); ++neighbor) 
		if (graph[v][neighbor] && !visited[neighbor])
			DFS(neighbor, graph, visited, component);
}

void fillOrder(int v, Graph graph, std::vector<bool>& visited, std::stack<int>& stack) 
{
	visited[v] = true;

	for (int neighbor = 0; neighbor < graph.number_of_vertex; ++neighbor)
		if (graph.adjancency_matrix[v][neighbor] && !visited[neighbor])
			fillOrder(neighbor, graph, visited, stack);

	stack.push(v);
}

std::vector<std::vector<int>> getTranspose(Graph graph) 
{
	int num_of_vert = graph.number_of_vertex;
	std::vector<std::vector<int>> transpose(num_of_vert, std::vector<int>(num_of_vert, 0));

	for (int v = 0; v < num_of_vert; ++v)
		for (int neighbor = 0; neighbor < num_of_vert; ++neighbor)
			transpose[v][neighbor] = graph.adjancency_matrix[neighbor][v];


	return transpose;
}

std::vector<std::vector<int>> findStronglyConnectedComponents(Graph graph) 
{
	int num_vert = graph.number_of_vertex;

	std::vector<bool> visited(num_vert, false);
	std::stack<int> stack;

	for (int v = 0; v < num_vert; ++v)
		if (!visited[v])
			fillOrder(v, graph, visited, stack);

	std::vector<std::vector<int>> transpose = getTranspose(graph);

	std::vector<std::vector<int>> stronglyConnectedComponents;

	visited.assign(num_vert, false);

	while (!stack.empty()) 
	{
		int v = stack.top();
		stack.pop();

		if (!visited[v]) 
		{
			std::vector<int> component;
			DFS(v, transpose, visited, component);
			stronglyConnectedComponents.push_back(component);
		}
	}

	return stronglyConnectedComponents;
}

void exercise2(Graph graph)
{
	if (!graph.isDirected()) 
	{
		bool connected = isGraphConnected(graph);
		if (connected) 
			std::cout << "Graph is connected.\n";
		else 
			std::cout << "Graph is not connected.\n";

		std::vector<std::vector<int>> components = findConnectedComponents(graph);
		std::cout << "Number of components: " << components.size();
		std::cout << "\nComponents: \n";
		for (const auto& component : components) 
		{
			for (int v : component) 
				std::cout << v+1 << " ";
			std::cout << "\n";
		}
	}
	else 
	{
		bool stronglyConnected = isStronglyConnected(graph);
		if (stronglyConnected) 
			std::cout << "Digraph is strongly connected.\n" ;
		else 
		{
			std::cout << "Digraph is not strongly connected.\n";
			bool weaklyConnected = isWeaklyConnected(graph);
			if (weaklyConnected)
				std::cout << "Digraph is weakly connected.\n";
			else
				std::cout << "Digraph is not weakly connected.\n";
		}

		std::vector<std::vector<int>> gr = convertToUndirectedGraph(graph);

		std::vector<std::vector<int>> strongComponents = findStronglyConnectedComponents(graph);
		std::vector<std::vector<int>> comp = findConnectedComponents(gr, graph.number_of_vertex);
		std::cout << "Number of components: " << comp.size();
		std::cout << "\nStrong components: \n";
		for (const auto& component : comp)
		{
			for (int v : component)
				std::cout << v + 1 << " ";
			std::cout << "\n";
		}

		std::cout << "\nNumber of strong components: " << strongComponents.size();
		std::cout << "\nStrong components: \n";
		for (const auto& component : strongComponents) 
		{
			for (int v : component)
				std::cout << v+1 << " ";
			std::cout <<"\n";
		}
	}
}