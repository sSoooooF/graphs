#pragma once
#include <vector>
#include "graph.h"

void dfs(Graph graph, int v, int parent, std::vector<int>& time_in, std::vector<int>& up, std::vector<bool>& visited, std::vector<bool>& articularPoints, std::vector<std::pair<int, int>>& bridges, int& time);

void dfs(std::vector<std::vector<int>> graph, int v, int parent, std::vector<int>& time_in, std::vector<int>& up, std::vector<bool>& visited, std::vector<bool>& articularPoints, std::vector<std::pair<int, int>>& bridges, int& time);

void findBridgesAndArticulationPoints(Graph graph, std::vector<bool>& articulationPoints, std::vector<std::pair<int, int>>& bridges);

void findBridgesAndArticulationPoints(std::vector<std::vector<int>> graph, std::vector<bool>& articulationPoints, std::vector<std::pair<int, int>>& bridges);

std::vector<std::vector<int>> convertToUndirectedGraph(Graph graph);

void exercise3(Graph graph);
