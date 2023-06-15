#pragma once
#include "graph.h"
#include <iostream>
#include <vector>

bool isBipartite(Graph graph, int source, std::vector<int>& color);

bool findAugmentingPath(Graph graph, int u, std::vector<int>& match, std::vector<bool>& visited);

int findMaximumMatchings(Graph graph, std::vector<int>& match);

void printMatchings(const std::vector<std::pair<int, int>>& matchings);

void exercise11(Graph graph);
