#pragma once
#include "graph.h"
#include <vector>

bool hasNegativeCycle(Graph graph);

std::vector<int> dijkstra(Graph graph, int start_vertex);

std::vector<int> bellmanFordMoore(Graph graph, int start_vertex);

std::vector<int> levit(Graph graph, int source);

void exercise6(Graph graph, int argc, const char* argv[]);
