#pragma once
#include "graph.h"
#include <vector>
#include <stack>

bool isGraphConnected(Graph graph);

bool isGraphConnected(std::vector<std::vector<int>> graph);

bool isStronglyConnected(Graph graph);

bool isWeaklyConnected(Graph graph);

std::vector<std::vector<int>> findConnectedComponents(Graph graph);


void exercise2(Graph graph);
