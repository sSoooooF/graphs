#include "exercise7.h"
#include "exercise6.h"
#include "graph.h"
#include <vector>
#include <queue>
#include <iostream>

#define INF 1000000

void dijkstra(std::vector<std::vector<int>>& adj_matrix, int source, std::vector<int>& distances) {
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
            if (adj_matrix[closest_vert][i] != INF && distances[i] > distances[closest_vert] + adj_matrix[closest_vert][i]) {
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
    
    // проверка на отрицательный цикл
    for (int j = 0; j < num_vert; j++) {
        for (int k = 0; k < num_vert; k++) {
            if (adj_matrix[j][k] != INF && j != k && distances[k] > distances[j] + adj_matrix[j][k]) {
                std::cout << "Graph contains a negative cycle." << std::endl;
                exit(0);
            }
        }
    }
}

// вычисление расстояний между всеми парами вершин в графе
void johnsonAlgorithm(Graph& graph) {
    int num_vert = graph.number_of_vertex;

    std::vector<std::vector<int>> adj_matrix(num_vert, std::vector<int>(num_vert));
    for (int i = 0; i < num_vert; i++)
        for (int j = 0; j < num_vert; j++)
            adj_matrix[i][j] = graph.adjancency_matrix[i][j];


    for (int i = 0; i < num_vert; i++) {
        for (int j = 0; j < num_vert; j++) {
            if (adj_matrix[i][j] == 0) {
                adj_matrix[i][j] = INF;
            }
        }
    }

    adj_matrix.push_back(std::vector<int>(num_vert, 0));
    for (int i = 0; i < num_vert + 1; i++) {
        adj_matrix[i].push_back(INF);
    }

    // h - функция кратчайших расстояний
    std::vector<int> h;
    bellmanFord(adj_matrix, num_vert, h);

    adj_matrix.pop_back();
    for (int i = 0; i < num_vert; i++) {
        adj_matrix[i].pop_back();
    }


    // изменение веса 
    for (int i = 0; i < num_vert; i++) {
        for (int j = 0; j < num_vert; j++) {
            if (adj_matrix[i][j] != INF) {
                adj_matrix[i][j] += h[i] - h[j];
            }
        }
    }


    std::vector<std::vector<int>> shortestPaths(num_vert, std::vector<int>(num_vert, INF));
    for (int i = 0; i < num_vert; i++) {
        std::vector<int> distances;
        dijkstra(adj_matrix, i, distances);
        for (int j = 0; j < num_vert; j++) {
            if (distances[j] != INF) {
                shortestPaths[i][j] = distances[j] + h[j] - h[i];
            }
            else {
                shortestPaths[i][j] = distances[j];
            }


        }

    }
    for (int i = 0; i< num_vert; i++)
        for (int j = 0; j < num_vert; j++)
            if (shortestPaths[i][j] != INF && i!=j)
                std::cout << i + 1 << "-" << j + 1 << "\t" << shortestPaths[i][j] << "\n";
}

void exercise7(Graph graph)
{

    for (int i = 0; i< graph.number_of_vertex; i++)
        for (int j= 0 ;j < graph.number_of_vertex; j++)
            if (graph.adjancency_matrix[i][j] < 0)
            {
                std::cout << "Graph contains edges with negative weight.\n";
                goto POINT;
            }


    POINT:
    std::cout << "Shortest paths lengths:\n";



	johnsonAlgorithm(graph);
}