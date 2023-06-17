#include "exercise11.h"
#include <vector>
#include "exercise3.h"


// ������� ��� ��������, �������� �� ���� ����������
bool isBipartite(Graph graph, int source, std::vector<int>& color) 
{
    int numVertices = graph.number_of_vertex;
    color[source] = 1;

    std::vector<int> visited(numVertices, false);

    for (int u = 0; u < numVertices; u++)
        if (!visited[u]) 
        {
            visited[u] = true;

            for (int v = 0; v < numVertices; v++)
                if (graph.adjancency_matrix[u][v] > 0) 
                {
                    if (color[v] == -1) 
                    {
                        color[v] = 1 - color[u];
                        visited[v] = true;
                    }
                    else if (color[v] == color[u])
                        return false;
                }
        }

    return true;
}

// ������� ��� ������ �������������� ���� � �����
bool findAugmentingPath(Graph graph, int u, std::vector<int>& match, std::vector<bool>& visited) {
    int numVertices = graph.number_of_vertex;
    visited[u] = true;

    for (int v = 0; v < numVertices; v++) {
        if (graph.adjancency_matrix[u][v] && !visited[v]) {
            visited[v] = true; // ���������� ���������� ������
            if (match[v] == -1 || findAugmentingPath(graph, match[v], match, visited)) {
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
    }

    return false;
}


// ������� ��� ���������� ������������ �������������
int findMaximumMatchings(Graph graph, std::vector<int>& match)
{
    int numVertices = graph.number_of_vertex;
   
    int maxMatching = 0;

    for (int u = 0; u < numVertices; u++)
        if (match[u] == -1) {
            std::vector<bool> visited(numVertices, false);
            if (findAugmentingPath(graph, u, match, visited))
                maxMatching++;  
        }

    return maxMatching;
}

// ������� ��� ������ ������ �������������
void printMatchings(std::vector<int>& match) 
{
    int numVertices = match.size();
    std::cout << "������ ����� �������������:\n";
    for (int u = 0; u < numVertices; u++) {
        if (match[u] != -1 && u < match[u]) {
            std::cout << u+1 << " -> " << match[u]+1 << std::endl;
        }
    }
}

void exercise11(Graph graph)
{
    std::vector<int> color(graph.number_of_vertex, -1);
    bool isBipart = isBipartite(graph, 0, color);

    if (isBipart)
    {
        std::cout << "���� ����������\n";

        std::vector<int> match(graph.number_of_vertex, -1);

        int maxMatching = findMaximumMatchings(graph, match);

        std::cout << "���������� ������������� " << maxMatching << std::endl;

        printMatchings(match);
    }
    else
    {
        std::cout << "���� �� ����������\n";
        return;
    }

}