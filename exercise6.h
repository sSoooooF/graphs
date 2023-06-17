#pragma once
#include "graph.h"
#include <vector>

bool hasNegativeCycle(Graph graph);

void dijkstra(Graph& graph, int start_vertex, std::vector<int>& distance);

void bellmanFordMoore(Graph& graph, int start_vertex, std::vector<int>& distance);

void levit(Graph& graph, int startVertex, std::vector<int>& distance);


void exercise6(Graph graph, int argc, const char* argv[]);
