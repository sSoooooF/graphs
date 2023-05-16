#pragma once
#include "graph.h"
#include <vector>

int findMinKeyVertex(std::vector<int>& key, std::vector<bool>& mstVector, int num_of_vert);

void printMST(std::vector<int>& parent, Graph graph);

void printMST(std::vector<int>& parent, std::vector<std::vector<int>>& undirGraph);

int findMST(Graph graph);

int findMST(std::vector<std::vector<int>>& undirGraph);

void exercise4(Graph graph);
