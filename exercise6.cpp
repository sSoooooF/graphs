#include "exercise6.h"
#include "graph.h"
#include <vector>
#include <queue>
#include <string>


#define INT_MAX 100000

struct Edge
{
	int source;
	int dest;
	int weight;

	Edge(int src, int dest, int w) : source(src), dest(dest), weight(w) {};
};


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

std::vector<int> levit(Graph graph, int source) {
	source--;
	int vert_num = graph.number_of_vertex;
	std::vector<int> dist(vert_num, INT_MAX);
	bool m0_not_empty = false;
	std::vector<int> M0;
	std::vector<int> M1;
	std::vector<int> M1_urgent;
	std::vector<int> M2;
	std::vector<bool> state(vert_num, 0);
	dist[source] = 0;
	state[source] = 1;
	M1_urgent.push_back(source);

	int vert;

	for (int i = 0; i < vert_num; i++) {
		if (i != source) {
			M0.push_back(i);
		}
	}


	while (!M1.empty() || !M1_urgent.empty()) {
		if (!M1_urgent.empty()) {
			vert = M1_urgent.front();
			M1_urgent.erase(std::remove(M1_urgent.begin(), M1_urgent.end(), vert), M1_urgent.end());
		}
		else if (!M1.empty()) {
			vert = M1.front();
			M1.erase(std::remove(M1.begin(), M1.end(), vert), M1.end());
		}
		std::vector<int> neighbors = graph.printAdjancencyList(vert);
		for (const auto& neighbor : neighbors) {
			std::vector<Edgeloh> edges = graph.printListOfEdges(vert);

			if (std::find(M0.begin(), M0.end(), neighbor) != M0.end()) {
				dist[neighbor] = dist[vert] + graph.adjancency_matrix[vert][neighbor];
				M0.erase(std::remove(M0.begin(), M0.end(), neighbor), M0.end());
				M1.push_back(neighbor);
			}

			if (std::find(M1.begin(), M1.end(), neighbor) != M1.end() || std::find(M1_urgent.begin(), M1_urgent.end(), neighbor) != M1_urgent.end()) {
				if (dist[neighbor] > dist[vert] + graph.adjancency_matrix[vert][neighbor]) {
					dist[neighbor] = dist[vert] + graph.adjancency_matrix[vert][neighbor];
				}
			}

			if (std::find(M2.begin(), M2.end(), neighbor) != M2.end()) {
				if (dist[neighbor] > dist[vert] + graph.adjancency_matrix[vert][neighbor]) {
					dist[neighbor] = dist[vert] + graph.adjancency_matrix[vert][neighbor];
					M2.erase(std::remove(M2.begin(), M2.end(), neighbor), M2.end());
					M1_urgent.push_back(neighbor);
				}
			}

		}

		M2.push_back(vert);
	}

	for (int i = 0; i < vert_num; i++) {
		if (state[i] == 0) {
			m0_not_empty = true;
		}
	}

	return dist;
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