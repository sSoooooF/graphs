#include "exercise10.h"
#include <queue>
#include <vector>
#include <climits>

// ������� ��� ������ ���� � ���������� ���� � ������� ������ � ������
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

    // ���������� true, ���� �������� ����� � ���������� ����
    return visited[sink];
}


int fordFalkerson(Graph graph, int source, int sink, std::vector<std::pair<int, int>>& flowEdges)
{
    int numVertices = graph.number_of_vertex;

    // ������� ���������� ����, �������������� ����� 0 ��� ���� �����
    std::vector<std::vector<int>> residualGraph(numVertices, std::vector<int>(numVertices));

    for (int u = 0; u < numVertices; u++) {
        for (int v = 0; v < numVertices; v++) {
            residualGraph[u][v] = graph.adjancency_matrix[u][v];
        }
    }

    // �������������� ����� � ���� �����
    int maxFlow = 0;

    // ����� ���� � ���������� ���� � ������� ������ � ������
    std::vector<int> parent(numVertices);
    while (bfs(residualGraph, parent, source, sink)) 
    {
        // ������� ����������� ���������� ����������� ����� �� ��������� ����
        int pathFlow = std::numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v]) 
        {
            int u = parent[v];
            pathFlow = std::min(pathFlow, residualGraph[u][v]);
        }

        // ��������� �������� ������ � ���������� ����
        for (int v = sink; v != source; v = parent[v]) 
        {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // ����������� �������� ������ ������
        maxFlow += pathFlow;
    }

    // ���������� ����� �����
    return maxFlow;
}


void printFlowEdges(std::vector<std::pair<int, int>>& flowEdges) 
{
    std::cout << "������ ����� � ��������� �������� ������:\n";
    for (const auto& edge : flowEdges) 
    {
        std::cout << edge.first << " -> " << edge.second << "\n";
    }
}

void exercise10(Graph graph)
{
    int source, sink;

    // �������������� ����������� ��������� � �����
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

    std::vector<std::pair<int, int>> flowEdges;
    int maxFlow = fordFalkerson(graph, source, sink, flowEdges);

    std::cout << maxFlow << " - maximum flow from.\n";
    printFlowEdges(flowEdges);
}
