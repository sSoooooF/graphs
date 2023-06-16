#pragma once
#include "graph.h"
#include <vector>

bool bfs(std::vector<std::vector<int>>& residualGraph, std::vector<int>& parent, int source, int sink);

std::pair<int, std::vector<std::vector<int>>> fordFalkerson(Graph graph, int source, int sink);

void printFlowEdges(int** graph, std::vector<std::vector<int>> residualGraph);

void exercise10(Graph graph);
