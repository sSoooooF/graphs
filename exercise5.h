#pragma once
#include <vector>
#include "graph.h"

std::pair<std::vector<int>, int> dijkstra(Graph graph, int start, int end);

void exercise5(Graph graph, int argc, const char** argv);
