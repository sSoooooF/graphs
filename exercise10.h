#pragma once
#include "graph.h"
#include <vector>

bool bfs(std::vector<std::vector<int>>& residualGraph, std::vector<int>& parent, int source, int sink);

std::pair<int, std::vector<std::vector<int>>> fordFalkerson(Graph graph, int source, std::vector<std::pair<int, int>>& flowEdges);


void printFlowEdges(const std::vector<std::pair<int, int>>& flowEdges, int** graph, std::vector<std::vector<int>> residualGraph);

void exercise10(Graph graph);
