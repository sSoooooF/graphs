#pragma once
#include "graph.h"
#include <vector>

bool hasNegativeCycle(Graph graph);

std::vector<int> dijkstra(std::vector<std::vector<int>> graph, int start_vertex, std::vector<int>& distance);

std::vector<int> bellmanFordMoore(std::vector<std::vector<int>> graph, int start_vertex, std::vector<int>& distance);

std::vector<int> levit(std::vector<std::vector<int>> graph, int startVertex, std::vector<int>& distance);


void exercise6(Graph graph, int argc, const char* argv[]);
