#include "graph.h"
#include <queue>
#include "exercise2.h"

#define MAX(a,b) a >= b ? a : b

int** closure(Graph graph)
{
	int num_of_vert = graph.number_of_vertex;
	int** matrix = graph.adjancency_matrix;
	for (int i = 0; i < num_of_vert; i++)
		for (int j = 0; j < num_of_vert; j++) {
			if (matrix[i][j] != 0 && matrix[j][i] == 0)
				matrix[j][i] = matrix[i][j];
			if (matrix[i][j] == 0 && matrix[j][i] != 0)
				matrix[i][j] = matrix[j][i];
		}
	return matrix;
}

void exercise2(Graph graph)
{
	setlocale(LC_ALL, "rus");
	int num_of_vert = graph.number_of_vertex;
	if (!graph.isDirected())
	{
		std::pair<int, int*> data = graph.bfsA();
		int cnt = data.first;
		int* components = data.second;
		if (cnt == 1) 
		{
			std::cout << "Граф связен!";
			return;
		}
		else 
		{
			std::cout << "В графе " << cnt-1 << " компонент связности!\n";
			int kolvo{};
			for (int i = 0; i < num_of_vert; i++)
				kolvo = MAX(kolvo, components[i]);
			for (int i = 0; i < kolvo; i++)
			{
				std::cout << "В " << i << " компоненте: ";
				for (int j = 0; j < num_of_vert; j++)
					if (i == components[j])
						std::cout << j << " ";
				std::cout << std::endl;
			}
			return;
		}
	}
	else
	{
		bool check = true;
		for (int i = 0; i < num_of_vert; i++)
		{
			if (graph.bfs(i) == false)
			{
				check = false;
				break;
			}
		}
		if (check == true)
		{
			std::cout << "Орграф сильно связный.\n";
			return;
		}
		else {
			int** matrix = graph.adjancency_matrix;
			graph.adjancency_matrix = closure(graph);
			std::pair<int, int*> data = graph.bfsA();
			graph.adjancency_matrix = matrix;
			int cnt = data.first;
			if (cnt == 1)
			{
				std::cout << "Орграф слабо связный." << "\n";
				return;
			}
			else
			{
				std::cout << "Орграф несвязный.\n";
				return;
			}
		}
	}
}