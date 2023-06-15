#pragma once
#include "graph.h"
#include <vector>

bool bfs(std::vector<std::vector<int>>& residualGraph, std::vector<int>& parent, int source, int sink);

int fordFalkerson(Graph graph, int source, int sink, std::vector<std::pair<int, int>>& flowEdges);

void printFlowEdges(std::vector<std::pair<int, int>>& flowEdges);

void exercise10(Graph graph);
