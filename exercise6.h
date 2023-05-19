#pragma once
#include "graph.h"
#include <vector>

std::vector<int> dijkstra(Graph graph, int start_vertex);

std::vector<int> bellmanFordMoore(Graph graph, int start_vertex);

std::vector<int> levit(Graph graph, int start_vertex);

void exercise6(Graph graph, int argc, const char* argv[]);
