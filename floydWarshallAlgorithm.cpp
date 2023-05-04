#pragma once
#include <algorithm>
#include "floydWarshallAlgorithm.h"

int** floydWarshallAlgorithm(int** matrix, int number_of_vertex)
{
	for (int k = 0; k < number_of_vertex; k++)
	{
		for (int i = 0; i < number_of_vertex; i++)
		{
			for (int j = 0; j < number_of_vertex; j++)
			{
				matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
		}
	}
	return matrix;
};