#include "exercise6.h"
#include "graph.h"
#include <vector>
#include <queue>
#include <string>


#define INT_MAX 100000

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
			if (graph.adjancency_matrix[u][i] && distances[u] + graph.adjancency_matrix[u][i] < distances[i])
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
				if (graph.adjancency_matrix[j][v] != 0 && distances[j] + graph.adjancency_matrix[j][v] < distances[v])
					distances[v] = distances[j] + graph.adjancency_matrix[j][v];

	return distances;
}

std::vector<int> levit(Graph graph, int start_vertex)
{
	int n = graph.number_of_vertex; // Количество вершин в графе

	std::vector<int> distance(n, INT_MAX);
	std::vector<int> parent(n, -1);
	std::vector<int> state(n, 2); // 2 - не посещена, 1 - в очереди, 0 - посещена

	std::queue<int> queue;

	distance[start_vertex] = 0;
	queue.push(start_vertex);
	state[start_vertex] = 1;

	while (!queue.empty()) {
		int currentNode = queue.front();
		queue.pop();
		state[currentNode] = 0;

		for (int i = 0; i < n; ++i) {
			if (graph.adjancency_matrix[currentNode][i] != INT_MAX) {
				int weight = graph.adjancency_matrix[currentNode][i];

				if (distance[currentNode] + weight < distance[i]) {
					distance[i] = distance[currentNode] + weight;
					parent[i] = currentNode;

					if (state[i] == 2) {
						queue.push(i);
						state[i] = 1;
					}
					else if (state[i] == 0) {
						queue.push(i);
						state[i] = 1;
					}
				}
			}
		}
	}
	return distance;
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
		answer = dijkstra(graph, start_vertex);
		break;
	case 2:
		answer = bellmanFordMoore(graph, start_vertex);
		break;
	case 3:
		answer = levit(graph, start_vertex);
		break;
	default:
		std::cout << "Error: Invalid algorithm option.";
		return;
	}

	/*int start_vertex = 6;
	std::vector<int> answer = levit(graph, start_vertex-1);*/

	

	
	std::cout << "Distances from vertex " << start_vertex+1 << ":\n";
	for (int i = 0; i < answer.size(); ++i) {
		if (answer[i] == INT_MAX) {
			std::cout << "Vertex " << i+1 << ": INF\n";
		}
		else {
			std::cout << "Vertex " << i+1 << ": " << answer[i] << "\n";
		}
	}
}