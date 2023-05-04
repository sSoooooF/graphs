#pragma once
#include "graph.h"

void help();

void consolOutput(int num_of_ver, int** matrix, int* vert, int diam, int rad, int* center, int* perif, int* eccen);

void consolOutput(int num_of_ver, int** matrix, int* vert_pos, int* vert_neg, int diam, int rad, int* center, int* perif, int* eccen);

int diameter(int* eccen, int num);

int radius(int* eccen, int num);

void exercise1(Graph graph);
