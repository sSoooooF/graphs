#include "graph.h"
#include "floydWarshallAlgorithm.h"
#include <vector>
#include "exercise1.h"

#define INF 999
#define MAX(a,b) a >= b ? a : b
#define MIN(a,b) a < b ? a : b

void help() { std::cout << "Автор работы Нуриев Наиль Ниязович\nГруппа М3О-211Б-21\nСписок ключей:\n-e 'edges_list_file_path'\n-m 'adjancency_matrix_file_path\n-l 'adjancency_list_file_path\n-o 'output_file_path\n"; }

void consolOutput(int num_of_ver, int** matrix, int* vert, int diam, int rad, int* center, int* perif, int* eccen)
{
	std::cout << "deg = ";
	for (int i = 0; i < num_of_ver; i++)
		if (i != num_of_ver - 1) std::cout << vert[i] << ", "; // Вывод степеней вершин в консоль
		else std::cout << vert[i];
	std::cout << "\nDistancies:";
	for (int i = 0; i < num_of_ver; i++) {
		std::cout << "\n";
		for (int j = 0; j < num_of_ver; j++)
			std::cout << matrix[i][j] << "\t";
	} // for
	std::cout << "\nEccentricity:\n";
	for (int i = 0; i < num_of_ver; i++) {
		if (i != num_of_ver - 1) std::cout << eccen[i] << ", ";
		else std::cout << eccen[i];
	}
	std::cout << "\nD = " << diam << "\nR = " << rad;
	std::cout << "\nZ = ";
	for (int i = 0; i < num_of_ver; i++)
		if (center[i] == 1) std::cout << i + 1 << " ";
	std::cout << "\nP = ";
	for (int i = 0; i < num_of_ver; i++)
		if (perif[i] == 1) std::cout << i + 1 << " ";
	std::cout << "\n";
} // consolOutput()

void consolOutput(int num_of_ver, int** matrix, int* vert_pos, int* vert_neg, int diam, int rad, int* center, int* perif, int* eccen)
{
	std::cout << "deg+ = ";
	for (int i = 0; i < num_of_ver; i++)
		if (i != num_of_ver - 1) std::cout << vert_pos[i] << ", "; // Вывод степеней вершин в консоль
		else std::cout << vert_pos[i];
	std::cout << "\ndeg- = ";
	for (int i = 0; i < num_of_ver; i++)
		if (i != num_of_ver - 1) std::cout << vert_neg[i] << ", "; // Вывод степеней вершин в консоль
		else std::cout << vert_neg[i];
	std::cout << "\nDistancies:";
	for (int i = 0; i < num_of_ver; i++) {
		std::cout << "\n";
		for (int j = 0; j < num_of_ver; j++)
			std::cout << matrix[i][j] << "\t";
	} // for
	std::cout << "\nEccentricity:\n";
	for (int i = 0; i < num_of_ver; i++) {
		if (i != num_of_ver - 1) std::cout << eccen[i] << ", ";
		else std::cout << eccen[i];
	}
	std::cout << "\nD = " << diam << "\nR = " << rad;
	std::cout << "\nZ = ";
	for (int i = 0; i < num_of_ver; i++)
		if (center[i] == 1) std::cout << i + 1 << " ";
	std::cout << "\nP = ";
	for (int i = 0; i < num_of_ver; i++)
		if (perif[i] == 1) std::cout << i + 1 << " ";
	std::cout << "\n";
} // consolOutput()

int diameter(int* eccen, int num)
{
	int diam = 0;
	for (int i = 0; i < num; i++)
		diam = MAX(diam, eccen[i]);
	return diam;
} // diameter()

int radius(int* eccen, int num)
{
	int rad = INF;
	for (int i = 0; i < num; i++)
		rad = MIN(rad, eccen[i]);
	return rad;
} // redius()

void exercise1(Graph graph)
{
	setlocale(LC_ALL, "rus"); // Для корректного отображения русского языка в консоли
	int** matrix = graph.adjancency_matrix;	// Копируем матрицу инцидентности из графа
	int num_of_ver = graph.number_of_vertex; // Копируем количество вершин из графа
	int* vert = new int[num_of_ver]; // Матрица для степеней вершин графа
	int* vert_pos = new int[num_of_ver];
	int* vert_neg = new int[num_of_ver];
	if (graph.isDirected()) {
		for (int i = 0; i < num_of_ver; i++) vert_pos[i] = 0;
		for (int i = 0; i < num_of_ver; i++) vert_neg[i] = 0;
		for (int i = 0; i < num_of_ver; i++)
			for (int j = 0; j < num_of_ver; j++)
				if (matrix[i][j] != 0) vert_neg[i]++;
		for (int i = 0; i < num_of_ver; i++)
			for (int j = 0; j < num_of_ver; j++)
				if (matrix[i][j] != 0) vert_pos[j]++;
	} 
	else {
		for (int i = 0; i < num_of_ver; i++) vert[i] = 0;
		for (int i = 0; i < num_of_ver; i++)
			for (int j = 0; j < num_of_ver; j++)
				if (matrix[i][j] != 0) vert[i]++; // Подстчет степеней вершин 
	}
	for (int i = 0; i < num_of_ver; i++)
		for (int j = 0; j < num_of_ver; j++)
			if (matrix[i][j] == 0) matrix[i][j] = INF;
	matrix = floydWarshallAlgorithm(graph.adjancency_matrix, graph.number_of_vertex); // Расчет матрицы алгоритмом Флойда-Уоршелла
	for (int i = 0; i < num_of_ver; i++) matrix[i][i] = 0;
	int* eccen = new int[num_of_ver];
	for (int i = 0; i < num_of_ver; i++) eccen[i] = 0;
	int j = 0;
	for (int i = 0; i < num_of_ver; i++)
		for (int j = 0; j < num_of_ver; j++)
			eccen[i] = MAX(eccen[i], matrix[i][j]);
	int diam = diameter(eccen, num_of_ver);
	int	rad = radius(eccen, num_of_ver);
	int* center = new int[num_of_ver];
	int* perif = new int[num_of_ver];
	for (int i = 0; i < num_of_ver; i++) {
		if (rad == diam) center[i] = perif[i] = 1;
		else if (eccen[i] == rad) center[i] = 1;
		else if (eccen[i] == diam) perif[i] = 1;
	} // for

	if (!graph.isDirected())
		consolOutput(num_of_ver, matrix, vert, diam, rad, center, perif, eccen);
	else
		consolOutput(num_of_ver, matrix, vert_pos, vert_neg, diam, rad, center, perif, eccen);
	return;
} // exercise1()