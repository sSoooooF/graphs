#pragma once
#include "graph.h"
#include <vector>

double getPathLength(Graph graph, std::vector<int>& path);

bool containsEdge(const std::vector<int>& path, int u, int v);

std::vector<int> antColony(Graph graph);

void exercise9(Graph graph, int argc, const char* argv[]);
