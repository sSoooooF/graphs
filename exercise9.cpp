#include "exercise9.h"
#include "graph.h"
#include <vector>
#include <climits>
#include <random>
#include <string>

double getPathLength(Graph graph,std::vector<int>& path) 
{
	double length = 0.0;
	for (int i = 0; i < path.size() - 1; i++) 
		length += graph.adjancency_matrix[path[i]][path[i + 1]];

	return length;
}

bool containsEdge(const std::vector<int>& path, int u, int v) {
	for (int i = 0; i < path.size() - 1; i++) 
		if ((path[i] == u && path[i + 1] == v) || (path[i] == v && path[i + 1] == u)) 
			return true;

	return false;
}

std::vector<int> antColony(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;
	int iter = num_of_vert * num_of_vert;
	double fer = 1.0;
	double vid = 1.0;
	double ispar = 0.5;

	std::vector<std::vector<double>> pheromones(num_of_vert, std::vector<double>(num_of_vert, 1.0));
	std::vector<int> best;
	double bestLength = INFINITY;

	srand(time(0));
	
	for (int i = 0; i < iter; ++i)
	{
		std::vector<std::vector<int>> antPath(num_of_vert);

		// построение пути для каждого муравья
		for (int ant = 0; ant < num_of_vert; ++ant)
		{
			std::vector<int> path(num_of_vert, -1);
			std::vector<bool> visited(num_of_vert, false);

			int curr = ant % num_of_vert;

			path[0] = curr;
			visited[curr] = true;


			// построение пути (опять)
			for (int step = 1; step < num_of_vert; ++step)
			{
				double sum = 0;

				// рассчет вероятносетй перехода
				for (int next = 0; next < num_of_vert; ++next)
					if (!visited[next])
						sum += pow(pheromones[curr][next], fer) * pow(1.0 / graph.adjancency_matrix[curr][next], vid);

				double q = (double)rand() / RAND_MAX;
				double probability = 0.0;

				// выборе вершины на рандом
				for (int next = 0; next < num_of_vert; ++next)
					if (!visited[next])
					{
						double prob = pow(pheromones[curr][next], fer) * pow(1.0 / graph.adjancency_matrix[curr][next], vid) / sum;
						probability += prob;

						if (q <= probability)
						{
							path[step] = next;
							visited[next] = true;
							curr = next;
							break;
						}
					}
			}

			antPath[ant] = path;
		}

		// обновление феромонов
		for (int i = 0; i < num_of_vert; ++i)
			for (int j = 0; j < num_of_vert; ++ j)
				if (i != j)
				{
					pheromones[i][j] *= ispar;

					for (int ant = 0; ant < num_of_vert; ++ant)
					{
						int pathlen = getPathLength(graph, antPath[ant]);

						if(containsEdge(antPath[ant], i, j))
							pheromones[i][j] += 1.0 / pathlen;
					}
				}

		// поиск лучшего пути
		for (int ant = 0; ant < num_of_vert; ++ant)
		{
			double pathlen = getPathLength(graph, antPath[ant]);

			if (pathlen < bestLength)
			{
				bestLength = pathlen;
				best = antPath[ant];
			}
		}
	}

	return best;
}

void exercise9(Graph graph, int argc, const char* argv[])
{
	int start_vertex = -1;

	for (int i = 0; i < argc; ++i)
	{
		std::string key = argv[i];
		if (key == "-n") {
			start_vertex = std::stoi(argv[i + 1]);
			break;
		}
	}

	std::vector<int> answer = antColony(graph);
	std::cout << "Гамильтоновый цикл:\n";
	for (int i = 0; i < graph.number_of_vertex; ++i)
		std::cout << answer[i] + 1 << "-" << answer[i] + 2 << "(" << graph.adjancency_matrix[answer[i]][answer[i] + 1] << ")\n";
}