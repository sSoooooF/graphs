#include "exercise7.h"
#include "graph.h"
#include <vector>


// алгоритм Джонсона
void johnson(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;

	std::vector<std::vector<int>> newgraph(num_of_vert, std::vector<int>(num_of_vert, 0)); // новый граф с num_of_vert+1 вершинами

	for (int i = 0; i < num_of_vert; ++i)
		for (int j = 0; j < num_of_vert; ++j)
			newgraph[i][j] = graph.adjancency_matrix[i][j];

	for (int i = 0; i < num_of_vert; ++i)
		newgraph[num_of_vert][i] = 0;

	std::vector<int> h(num_of_vert + 1, 0);
	std::vector<int> distance(num_of_vert + 1, 0);
	distance[num_of_vert] = 0;

	for (int i = 0; i < num_of_vert; ++i)
		for (int j = 0; j <= num_of_vert; ++j)
			for (int k = 0; k <= num_of_vert; ++k)
				if (newgraph[j][k] != INT_MAX && distance[j] != INT_MAX && distance[j] + newgraph[j][k] < distance[k])
					distance[k] = distance[j] + newgraph[j][k];

	// проверка на отрицательный цикл
	for (int i = 0; i < num_of_vert; ++i)
		for (int j = 0; j < num_of_vert; ++j)
			if (newgraph[i][j] != INT_MAX && distance[i] != INT_MAX && distance[i] + newgraph[i][j] < distance[j])
			{
				std::cout << "Граф содержит отрицательный цикл\n";
				return;
			}

	newgraph.pop_back(); // удаляем искусственную вершину
	for (int i = 0; i < num_of_vert; ++i)
		newgraph[i].pop_back();

	for (int i = 0; i < num_of_vert; ++i)
		for (int j = 0; j < num_of_vert; ++j)
			if (newgraph[i][j] != INT_MAX)
				newgraph[i][j] = newgraph[i][j] + distance[i] - distance[j];

	for (int i = 0; i < num_of_vert; ++ i)\
	{
		for (int j = 0; j < num_of_vert; ++j)
			std::cout << i + 1 << "-" << j + 1 << "(" << newgraph[i][j] << ")\n";
		std::cout << '\n';
	}
}

void exercise7(Graph graph)
{
	johnson(graph);
}