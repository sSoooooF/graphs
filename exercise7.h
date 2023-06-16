#pragma once
#include "graph.h"


void dijkstra1(std::vector<std::vector<int>>& adj_matrix, int source, std::vector<int>& distances);

void bellmanFord(std::vector<std::vector<int>>& adj_matrix, int source, std::vector<int>& distances);

std::vector<std::vector<int>> johnson(Graph graph);

void exercise7(Graph graph);
