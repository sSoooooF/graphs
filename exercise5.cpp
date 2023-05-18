#include "exercise5.h"
#include "graph.h"
#include <vector>
#include <queue>
#include <string>

std::pair<std::vector<int>, int> dijkstra(Graph graph, int start, int end)
{
	int num_of_vert = graph.number_of_vertex;
	std::vector<int> distances(num_of_vert, INT_MAX);
	std::vector<int> parent(num_of_vert, -1);
	std::vector<bool> visited(num_of_vert, false);

	distances[start] = 0;

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
	pq.push({ distances[start] ,start});

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		if (visited[u])
			continue;

		visited[u] = true;

		for (int i = 0; i < num_of_vert; ++i)
		{
			if (graph.adjancency_matrix[u][i] != 0 && !visited[i] && distances[u] != INT_MAX && distances[u] + graph.adjancency_matrix[u][i] < distances[i])
			{
				distances[i] = distances[u] + graph.adjancency_matrix[u][i];
				parent[i] = u;
				pq.push({ distances[i],i });
			}
		}
	}

	std::vector<int> path;
	int curr_vert = end;
	while (curr_vert != -1)
	{
		path.insert(path.begin(), curr_vert);
		curr_vert = parent[curr_vert];
	}

	return { path, distances[end] };
}

void exercise5(Graph graph, int argc, const char** argv)
{
	int str = 5;
	int startVertex = str-1;
	int end = 4;
	int endVertex = end - 1;

	/*for (int i = 1; i < argc; i += 2) {
		std::string key = argv[i];
		std::string value = argv[i + 1];

		if (key == "-n") {
			startVertex = std::stoi(value);
		}
		else if (key == "-d") {
			endVertex = std::stoi(value);
		}
	}

	if (startVertex == -1 || endVertex == -1) {
		std::cout << "Start and end vertices must be specified!\n";
		return;
	}*/

	std::pair<std::vector<int>, int> answer = dijkstra(graph, startVertex, endVertex);

	std::cout << "Кратчайший путь от вершины " << startVertex << " до вершины " << endVertex << ":\n";
	for (int i = 0; i < answer.first.size(); ++i)
	{
		std::cout << answer.first[i];
		if (i != answer.first.size() - 1)
			std::cout << "->";
	}
	std::cout << "\nДлина геодезической цепи: " << answer.second;

}