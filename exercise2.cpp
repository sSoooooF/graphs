#include "graph.h"
#include <queue>
#include "exercise2.h"
#include "floydWarshallAlgorithm.h"

#define MAX(a,b) a >= b ? a : b

int** closure(Graph graph)
{
	int** matrix = graph.adjancency_matrix;
	int num_of_vert = graph.number_of_vertex;
	for (int i = 0; i < num_of_vert; i++)
		for (int j = 0; j < num_of_vert; j++)
		{
			if (matrix[i][j] == 0 && matrix[j][i] != 0)
				matrix[i][j] = matrix[j][i];
			if (matrix[j][i] == 0 && matrix[i][j] != 0)
				matrix[j][i] = matrix[i][j];
		}
	return matrix;
}

void bfs(Graph graph, bool* used, int* comp, int v, int c_num)
{
	used[v] = true;
	comp[v] = c_num;
	for (int i = 0; i < graph.number_of_vertex; i++)
	{
		if (graph.adjancency_matrix[v][i] == 0)
			continue;
		if (!used[i])
			bfs(graph, used, comp, i, c_num);
	}
}

void bfs(int** matrix, int num_of_vert, bool* used, int* comp, int v, int c_num)
{
	used[v] = true;
	comp[v] = c_num;
	for (int i = 0; i < num_of_vert; i++)
	{
		if (matrix[v][j] == 0)
			continue;
		if (!used[i])
			bfs(matrix, num_of_vert, used, comp, i, c_num);
	}
}

void exercise2(Graph graph)
{
	setlocale(LC_ALL, "rus");
	int num_of_vert = graph.number_of_vertex;
	bool* used = new bool[num_of_vert];
	for (int i = 0; i < num_of_vert; i++)
		used[i] = false;
	int* comp = new int[num_of_vert];
	for (int i = 0; i < num_of_vert; i++)
		comp[i] = 0;
	int c_num = 1;
	if (!graph.isDirected())
	{
		for (int  i =0 ; i <num_of_vert;i++)
			if (!used[i]) 
			{
				bfs(graph, used, comp, i, c_num);
				c_num++;
			}
		bool check = true;
		for (int i = 1; i < num_of_vert; i++)
			if (comp[0] != comp[i])
			{
				check = false;
				break;
			}
		if (check == true)
		{
			std::cout << "Граф несвязный\n";
			for (int i = 0; i < num_of_vert; i++)
				std::cout << "Вершина " << i << " в компоненте " << comp[i] << "\n";
			return;
		}
		else 
		{
			std::cout << "Граф связный\nВсе вершины в одной компоненте.";
			return;
		}
	}
	else
	{
		int** matrix = closure(graph);
		for (int i = 0; i < num_of_vert; i++)
			if (!used[i])
			{
				bfs(matrix, num_of_vert, used, comp, i, c_num);
				c_num++;
			}
		bool check = true;
		for (int i = 1; i < num_of_vert; i++)
			if (comp[0] != comp[i])
			{
				check = false;
				break;
			}
		if (check = true)
		{
			std::cout << "Граф слабо связен\n";
			return;
		}

		
	}
}