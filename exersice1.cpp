#include "graph.h"
#include "floydWarshall.h"
#include "exersice1.h"
#include <vector>

#define INF 99999
#define MAX(a,b) a >= b ? a : b
#define MIN(a,b) a < b ? a : b

void consolOutput(int num_of_ver, int** matrix, int* vert, int diam, int rad, int* center, int* perif, int* eccen)
{
	std::cout << "deg = ";
	for (int i = 0; i < num_of_ver; i++)
		if (i != num_of_ver - 1) std::cout << vert[i] << ", "; // ����� �������� ������ � �������
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
} // consolOutput

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
	setlocale(LC_ALL, "rus"); // ��� ����������� ����������� �������� ����� � �������
	int** matrix = graph.adjancency_matrix;	// �������� ������� ������������� �� �����
	int num_of_ver = graph.number_of_vertex; // �������� ���������� ������ �� �����
	int* vert = new int[num_of_ver]; // ������� ��� �������� ������ �����
	for (int i = 0; i < num_of_ver; i++) vert[i] = 0;
	for (int i = 0; i < num_of_ver; i++)
		for (int j = 0; j < num_of_ver; j++)
			if (matrix[i][j] != 0) vert[i]++; // �������� �������� ������ 
	for (int i = 0; i < num_of_ver; i++)
		for (int j = 0; j < num_of_ver; j++)
			if (matrix[i][j] == 0) matrix[i][j] = INF;
	matrix = floydWarshallAlgorithm(graph.adjancency_matrix, graph.number_of_vertex); // ������ ������� ���������� ������-��������
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
		if (eccen[i] == rad) center[i] = 1;
		else if (eccen[i] == diam) perif[i] = 1;
	} // for
	consolOutput(num_of_ver, matrix, vert,diam,rad, center, perif, eccen);
	return;
} // exercise1()