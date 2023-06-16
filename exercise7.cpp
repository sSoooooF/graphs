#include "exercise7.h"
#include "exercise6.h"
#include "graph.h"
#include <vector>
#include <limits>
#include <queue>
#include <iostream>

#define INF std::numeric_limits<int>::max()



void dijkstra1(std::vector<std::vector<int>>& adj_matrix, int source, std::vector<int>& distances) {
    int num_vert = adj_matrix[0].size();
    std::vector<bool> visited(num_vert, false);
    distances.resize(num_vert, INF);
    distances[source] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> queue;
    queue.push(std::make_pair(0, source));

    while (!queue.empty()) {
        int closest_vert = queue.top().second;
        queue.pop();

        if (visited[closest_vert]) {
            continue;
        }
        visited[closest_vert] = true;

        for (int i = 0; i < num_vert; i++) {
            if (adj_matrix[closest_vert][i] != 0 && distances[i] > distances[closest_vert] + adj_matrix[closest_vert][i]) {
                distances[i] = distances[closest_vert] + adj_matrix[closest_vert][i];
                queue.push(std::make_pair(distances[i], i));
            }
        }
    }
}

void bellmanFord(std::vector<std::vector<int>>& adj_matrix, int source, std::vector<int>& distances) {
    int num_vert = adj_matrix[0].size();
    distances.resize(num_vert, INF);
    distances[source] = 0;

    for (int i = 0; i < num_vert - 1; i++) {
        for (int j = 0; j < num_vert; j++) {
            for (int k = 0; k < num_vert; k++) {
                if (adj_matrix[j][k] != INF && j != k && distances[k] > distances[j] + adj_matrix[j][k]) {
                    if (distances[k] == INF) {
                        distances[k] = adj_matrix[j][k];
                    }
                    else {
                        distances[k] = distances[j] + adj_matrix[j][k];
                    }

                }
            }
        }
    }
}

std::vector<std::vector<int>> johnson(Graph graph) {
    int num_vert = graph.number_of_vertex;
    std::vector<std::vector<int>> adj_mat(num_vert, std::vector<int>(num_vert, INF));
    for (int i = 0; i < num_vert; i++) {
        for (int j = 0; j < num_vert; j++) {
            if (graph.adjancency_matrix[i][j] != 0 || i == j) {
                adj_mat[i][j] = graph.adjancency_matrix[i][j];
            }
        }
    }

    adj_mat.push_back(std::vector<int>(num_vert, 0));
    for (int i = 0; i < num_vert + 1; i++) {
        adj_mat[i].push_back(INF);
    }

    std::vector<int> h;
    bellmanFord(adj_mat, num_vert, h);


    adj_mat.pop_back();
    for (int i = 0; i < num_vert; i++) {
        adj_mat[i].pop_back();
    }

    for (int i = 0; i < num_vert; i++) {
        for (int j = 0; j < num_vert; j++) {
            if (adj_mat[i][j] != INF) {
                adj_mat[i][j] += h[i] - h[j];
            }
        }
    }


    std::vector<std::vector<int>> shortestPaths(num_vert, std::vector<int>(num_vert, 0));
    for (int i = 0; i < num_vert; i++) {
        std::vector<int> distances;
        dijkstra1(adj_mat, i, distances);
        for (int j = 0; j < num_vert; j++) {
            if (distances[j] != INF) {
                shortestPaths[i][j] = distances[j] + h[j] - h[i];
            }
            else {
                shortestPaths[i][j] = distances[j];
            }
        }

    }
    return shortestPaths;
}

void exercise7(Graph graph)
{
	std::vector<std::vector<int>> answer = johnson(graph);

    for (int i = 0; i < graph.number_of_vertex; ++i)
        for (int j = 0; j < graph.number_of_vertex; ++j)
            if (i != j)
            {
                std::cout << i + 1 << "-" << j + 1 << "(" << answer[i][j] << ")\n";
            }
}