#include "graph.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	graph Graph;
	int index = 1;




	while (argv) {
		if (argv[index] == "-e") 
		{
			Graph.readGraphEdges(argv[++index]);
			index++;
		}
		if (argv[index] == "-m") 
		{
			Graph.readGraphMatrix(argv[++index]);
			index++;
		}
		if (argv[index] == "-l") 
		{

		}
	}
}





void floydWarshall(int **matrix, int number_of_vertex) 
{
	for (int k = 0; k < number_of_vertex; k++) 
	{
		for (int i = 0; i < number_of_vertex; i++) 
		{
			for (int j = 0; j < number_of_vertex; j++)
			{
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
		}
	}
}