#include "exercise6.h"
#include "graph.h"
#include <vector>
#include <queue>
#include <string>
#include <limits>

#define INT_MAX std::numeric_limits<int>::max()

bool hasNegativeCycle(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	int **distances = graph.adjancency_matrix;

	for (int k = 0; k < num_of_vert; ++k)
		for (int i = 0; i < num_of_vert; ++i)
			for (int j = 0; j < num_of_vert; ++j)
				distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);

	for (int i = 0; i < num_of_vert; ++i)
		if (distances[i][i] < 0)
			return true;

	return false;
}


std::vector<int> dijkstra(std::vector<std::vector<int>> graph, int startVertex, std::vector<int>& distance)
{
	int numVertices = graph.size();
	std::vector<bool> visited(numVertices, false); // Посещенные вершины

	distance[startVertex] = 0; // Расстояние до стартовой вершины равно 0

	for (int i = 0; i < numVertices - 1; ++i)
	{
		int minDistance = INT_MAX;
		int minVertex = -1;

		// Находим вершину с минимальным расстоянием
		for (int j = 0; j < numVertices; ++j)
		{
			if (!visited[j] && distance[j] < minDistance)
			{
				minDistance = distance[j];
				minVertex = j;
			}
		}

		if (minVertex == -1)
			break;

		visited[minVertex] = true;

		// Обновляем расстояния до смежных вершин
		for (int j = 0; j < numVertices; ++j)
		{
			if (!visited[j] && graph[minVertex][j] != INT_MAX && distance[minVertex] != INT_MAX
				&& distance[minVertex] + graph[minVertex][j] < distance[j])
			{
				distance[j] = distance[minVertex] + graph[minVertex][j];
			}
		}
	}

	return distance;
}

std::vector<int> bellmanFordMoore(std::vector<std::vector<int>> graph, int startVertex, std::vector<int>& distance)
{
	int numVertices = graph.size();

	distance[startVertex] = 0; // Расстояние до стартовой вершины равно 0

	for (int i = 0; i < numVertices - 1; ++i)
	{
		for (int j = 0; j < numVertices; ++j)
		{
			for (int k = 0; k < numVertices; ++k)
			{
				if (graph[j][k] != INT_MAX && distance[j] != INT_MAX && distance[j] + graph[j][k] < distance[k])
				{
					distance[k] = distance[j] + graph[j][k];
				}
			}
		}
	}

	return distance;
}

std::vector<int> levit(std::vector<std::vector<int>> graph, int startVertex, std::vector<int>& distance)
{
	int numVertices = graph.size();
	std::vector<int> level(numVertices, INT_MAX); // Уровень каждой вершины
	std::queue<int> queue;
	std::vector<int> inQueue(numVertices, false); // Вершины, находящиеся в очереди

	distance[startVertex] = 0; // Расстояние до стартовой вершины равно 0
	level[startVertex] = 0; // Уровень стартовой вершины равен 0

	queue.push(startVertex);
	inQueue[startVertex] = true;

	while (!queue.empty())
	{
		int currentVertex = queue.front();
		queue.pop();
		inQueue[currentVertex] = false;

		// Обновляем расстояния до смежных вершин
		for (int i = 0; i < numVertices; ++i)
		{
			if (graph[currentVertex][i] != INT_MAX && distance[currentVertex] != INT_MAX
				&& distance[currentVertex] + graph[currentVertex][i] < distance[i])
			{
				distance[i] = distance[currentVertex] + graph[currentVertex][i];

				if (!inQueue[i])
				{
					queue.push(i);
					inQueue[i] = true;
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

	std::vector<int> distance(graph.number_of_vertex, INT_MAX);

	if (hasNegativeCycle(graph))
	{
		std::cout << "Граф имеет отрицательный цикл!";
		return;
	}

	std::vector<std::vector<int>> grap(graph.number_of_vertex, std::vector<int>(graph.number_of_vertex, INT_MAX));

	for (int i = 0; i < graph.number_of_vertex; ++i)
		for (int j = 0; j < graph.number_of_vertex; ++j)
			if (graph.adjancency_matrix[i][j] != 0 || i == j)
				grap[i][j] = graph.adjancency_matrix[i][j];


	switch (algorithm)
	{
	case 1:
		dijkstra(grap, start_vertex, distance);
		break;
	case 2:
		bellmanFordMoore(grap, start_vertex, distance);
		break;
	case 3:
		levit(grap, start_vertex, distance);
		break;
	default:
		std::cout << "Error: Invalid algorithm option.";
		return;
	}

	
	std::cout << "Distances from vertex " << start_vertex+1 << ":\n";
	for (int i = 0; i < distance.size(); ++i) {
		if (distance[i] == INT_MAX) {
			std::cout << "Vertex " << i+1 << ": INF\n";
		}
		else {
			std::cout << "Vertex " << i+1 << ": " << distance[i] << "\n";
		}
	}
}