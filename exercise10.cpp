#include "exercise10.h"
#include <queue>
#include <vector>
#include <climits>

// Функция для поиска пути в остаточной сети с помощью обхода в ширину
bool bfs(std::vector<std::vector<int>>& residualGraph, std::vector<int>& parent, int source, int sink) {
    int numVertices = residualGraph.size();
    std::vector<bool> visited(numVertices, false);

    std::queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // Возвращаем true, если достигли стока в остаточной сети
    return visited[sink];
}


std::pair<int, std::vector<std::vector<int>>> fordFalkerson(Graph graph, int source, int sink)
{
    int numVertices = graph.number_of_vertex;

    // Создаем остаточную сеть, инициализируем поток 0 для всех ребер
    std::vector<std::vector<int>> residualGraph(numVertices, std::vector<int>(numVertices));

    for (int u = 0; u < numVertices; u++) {
        for (int v = 0; v < numVertices; v++) {
            residualGraph[u][v] = graph.adjancency_matrix[u][v];
        }
    }

    // Инициализируем поток в сети нулем
    int maxFlow = 0;

    // Поиск пути в остаточной сети с помощью обхода в ширину
    std::vector<int> parent(numVertices, -1);

    while (bfs(residualGraph, parent, source, sink)) 
    {
        // Находим минимальную пропускную способность ребер на найденном пути
        int pathFlow = std::numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v]) 
        {
            int u = parent[v];
            pathFlow = std::min(pathFlow, residualGraph[u][v]);
        }

        // Обновляем значения потока в остаточной сети
        for (int v = sink; v != source; v = parent[v]) 
        {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Увеличиваем значение общего потока
        maxFlow += pathFlow;
    }
    // Возвращаем общий поток
    return { maxFlow, residualGraph };
}

void printFlowEdges(int** graph, std::vector<std::vector<int>> residualGraph) {
    std::cout << "Список ребер с указанием величины потока:\n";
    for (int u = 0; u < residualGraph.size(); u++) {
        for (int v = 0; v < residualGraph[u].size(); v++) {
            if (graph[u][v] > 0) {
                // Если есть ребро в графе, добавляем его в список
                int flow = graph[u][v] - residualGraph[u][v];
                std::cout << u + 1 << " " << v + 1 << " " << flow << "/" << graph[u][v] << "\n";
            }
            else if (graph[v][u] == 0 && residualGraph[v][u] > 0) {
                // Если прямой поток равен нулю, но есть обратный поток, добавляем его в список
                std::cout << u + 1 << " " << v + 1 << " " << residualGraph[v][u] << "/" << graph[v][u] << "\n";
            }
        }
    }
}

void exercise10(Graph graph)
{
    int source, sink;


    // Автоматическое определение источника и стока
    for (int i = 0; i < graph.number_of_vertex; i++) {
        int outgoingEdges = 0;
        int incomingEdges = 0;

        for (int j = 0; j < graph.number_of_vertex; j++) {
            if (graph.adjancency_matrix[i][j] > 0)
                outgoingEdges++;
            if (graph.adjancency_matrix[j][i] > 0)
                incomingEdges++;
        }

        if (outgoingEdges > 0 && incomingEdges == 0)
            source = i;
        else if (outgoingEdges == 0 && incomingEdges > 0)
            sink = i;
    }

    auto pr = fordFalkerson(graph, source, sink);

    int maxFlow = pr.first;
    auto resid = pr.second;

    

    std::cout << maxFlow << " - maximum flow from " << source+1 << " to " << sink+1 << ".\n";
    printFlowEdges(graph.adjancency_matrix, resid);
}
