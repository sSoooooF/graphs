#pragma once
#include "graph.h"
#include <vector>

void exercise4(Graph graph, int argc, const char* argv[]);

int findMinKeyVertex(std::vector<int>& key, std::vector<bool>& mst_vector, int num_of_vert);

void findMSTBr(Graph graph);

void findMSTBr(std::vector<std::vector<int>> undirGraph, int num_of_vert);

void findMSTKr(Graph graph);

void findMSTKr(std::vector<std::vector<int>>& undirGraph, int num_of_vert);

void findMSTPr(Graph graph);

void findMSTPr(std::vector<std::vector<int>>& undirGraph, int num_of_vert);
