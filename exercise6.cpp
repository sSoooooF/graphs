#include "exercise6.h"
#include "graph.h"
#include <vector>
#include <queue>
#include <string>

bool hasNegativeCycle(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	int** distances = new int* [num_of_vert];
	for (int i = 0; i < num_of_vert; ++i)
		distances[i] = new int[num_of_vert];

	distances = graph.adjancency_matrix;

	for (int k = 0; k < num_of_vert; ++k)
		for (int i = 0; i < num_of_vert; ++i)
			for (int j = 0; j < num_of_vert; ++j)
				distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);

	for (int i = 0; i < num_of_vert; ++i)
		if (distances[i][i] < 0)
			return true;

	return false;
}


std::vector<int> dijkstra(Graph graph, int start_vertex)
{
	int num_of_vert = graph.number_of_vertex;
	std::vector<int> distances(num_of_vert, INT_MAX);
	std::vector<bool> visited(num_of_vert, false);

	distances[start_vertex] = 0;

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
	pq.push({ distances[start_vertex] ,start_vertex});

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		if (visited[u])
			continue;

		visited[u] = true;

		for (int i = 0; i < num_of_vert; ++i)
			if (graph.adjancency_matrix[u][i] && distances[u] != INT_MAX && distances[u] + graph.adjancency_matrix[u][i] < distances[i])
			{
				distances[i] = distances[u] + graph.adjancency_matrix[u][i];
				pq.push({ distances[i],i });
			}
	}

	return distances;
}

std::vector<int> bellmanFordMoore(Graph graph, int start_vertex)
{
	int num_of_vert = graph.number_of_vertex;
	std::vector<int> distances(num_of_vert, INT_MAX);

	distances[start_vertex] = 0;

	for (int i = 0; i < num_of_vert - 1; ++i)
		for (int j = 0; j < num_of_vert; ++j)
			for (int v = 0; v < num_of_vert; ++v)
				if (graph.adjancency_matrix[j][v] != 0 && distances[j] != INT_MAX && distances[j] + graph.adjancency_matrix[j][v] < distances[v])
					distances[v] = distances[j] + graph.adjancency_matrix[j][v];

	return distances;
}

std::vector<int> levit(Graph graph, int start_vertex)
{
	int num_of_vert = graph.number_of_vertex;
	std::vector<int> distances(num_of_vert, INT_MAX);
	std::vector<bool> visited(num_of_vert, false);

	distances[start_vertex] = 0;

	std::deque<int> q;
	q.push_back(start_vertex);

	while (!q.empty())
	{
		int u = q.front();
		q.pop_front();

		visited[u] = true;

		for (int i = 0; i < num_of_vert;++i)
			if (graph.adjancency_matrix[u][i] != 0 && distances[u] != INT_MAX && distances[u] + graph.adjancency_matrix[u][i] < distances[i])
			{
				distances[i] = distances[u] + graph.adjancency_matrix[u][i];

				if (!visited[i])
				{
					if (!q.empty() && distances[i] < distances[q.front()])
						q.push_back(i);
					else
						q.push_back(i);
					visited[i] = true;
				}
			}
	}

	return distances;
}

void exercise6(Graph graph, int argc, const char* argv[])
{
	int algorithm = 0;
	int start_vertex = -1;

	for (int i = 0; i < argc; ++i)
	{
		std::string key = argv[i];
		if (key == "-d") {
			algorithm = 1;
			break;
		}
		else if (key == "-b") {
			algorithm = 2;
			break;
		}
		else if (key == "-t") {
			algorithm = 3;
			break;
		}
	}

	for (int i = 0; i < argc; ++i)
	{
		std::string key = argv[i];
		if (key == "-n") {
			start_vertex = std::stoi(argv[i+1]);
			break;
		}
	}

	std::vector<int> answer;

	if (hasNegativeCycle(graph))
	{
		std::cout << "Граф имеет отрицательный цикл!";
		return;
	}

	switch (algorithm)
	{
	case 1:
		answer = dijkstra(graph, start_vertex-1);
		break;
	case 2:
		answer = bellmanFordMoore(graph, start_vertex-1);
		break;
	case 3:
		answer = levit(graph, start_vertex-1);
		break;
	default:
		std::cout << "Error: Invalid algorithm option.";
		return;
	}

	/*int start_vertex = 6;
	std::vector<int> answer = levit(graph, start_vertex-1);*/

	

	
	std::cout << "Distances from vertex " << start_vertex << ":\n";
	for (int i = 0; i < answer.size(); ++i) {
		if (answer[i] == INT_MAX) {
			std::cout << "Vertex " << i+1 << ": INF\n";
		}
		else {
			std::cout << "Vertex " << i+1 << ": " << answer[i] << "\n";
		}
	}
}