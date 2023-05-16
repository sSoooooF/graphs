#pragma once
#include "graph.h"
#include <vector>
#include <stack>

bool isGraphConnected(Graph graph, int v);

void bfs(Graph graph, int v, std::vector<bool>& visited, std::vector<int>& component);

std::vector<std::vector<int>> findConnectedComponents(Graph graph);

void dfs(Graph graph, int v, std::vector<bool>& visited, std::stack<int>& stk);

void dfsTranspose(std::vector<std::vector<int>> transposeGraph, int v, std::vector<bool>& visited, std::vector<int>& component);

void dfsTranspose(std::vector<std::vector<int>> transposeGraph, int v, std::vector<bool>& visited);

bool isDigraphWeaklyConnected(Graph graph);

bool isDigraphStronglyConnected(Graph graph);

std::vector<std::vector<int>> findStronglyConnectedComponents(Graph graph);

void exercise2(Graph graph);
