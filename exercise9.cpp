#include "exercise9.h"
#include "graph.h"
#include <vector>
#include <climits>
#include <random>
#include <string>


const double alpha = 1.0;
const double beta = 5.0;


struct Edge
{
	int source;
	int destination;
    int weight;
};

// инициализации феромона на ребрах
std::vector<std::vector<double>> initializePheromones(int numvert) 
{
	std::vector<std::vector<double>> pheromones(numvert, std::vector<double>(numvert, 0.1));
	return pheromones;
}

std::vector<Edge> initializeGraph(Graph grap) 
{
    int numVertices = grap.number_of_vertex;
    std::vector<Edge> graph;

    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (grap.adjancency_matrix[i][j] > 0) {
                graph.push_back({ i, j, grap.adjancency_matrix[i][j] });
            }
        }
    }

    return graph;
}

// выбор следующей вершины
int getNextVertex(std::vector<Edge>& graph, std::vector<std::vector<double>>& pheromones, std::vector<bool>& visited, int currentVertex)
{
    double total = 0.0;
    int numVertices = pheromones.size();

    for (const auto& edge : graph)
        if (edge.source == currentVertex && !visited[edge.destination]) 
        {
            total += std::pow(pheromones[edge.source][edge.destination], alpha) *
                std::pow(1.0 / graph[edge.source].weight, beta);
        }

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double random = distribution(generator);
    double cumulativeProbability = 0.0;

    for (const auto& edge : graph) {
        if (edge.source == currentVertex && !visited[edge.destination]) {
            double probability = (std::pow(pheromones[edge.source][edge.destination], alpha) *
                std::pow(1.0 / graph[edge.source].weight, beta)) / total;
            cumulativeProbability += probability;

            if (random <= cumulativeProbability)
                return edge.destination;
        }
    }

    return -1;  // Нет доступных вершин
}

void updatePheromones(std::vector<std::vector<double>>& pheromones, std::vector<Edge>& graph, std::vector<std::vector<int>>& paths)
{
    int numVertices = pheromones.size();

    for (auto& row : pheromones) {
        for (auto& pheromone : row) {
            pheromone *= (1.0 - 0.1);  // Испарение феромона
        }
    }

    for (const auto& antPath : paths) {
        double pathLength = 0.0;

        for (size_t i = 0; i < antPath.size() - 1; ++i) {
            int source = antPath[i];
            int destination = antPath[i + 1];
            pathLength += graph[source].weight;
        }

        for (size_t i = 0; i < antPath.size() - 1; ++i) {
            int source = antPath[i];
            int destination = antPath[i + 1];
            pheromones[source][destination] += 1.0 / pathLength;
            pheromones[destination][source] += 1.0 / pathLength;
        }
    }
}

std::vector<int> findHamiltonianCycle(Graph gr, std::vector<Edge>& graph, int startVertex)
{
    int numVertices = gr.number_of_vertex;
    std::vector<std::vector<double>> pheromones = initializePheromones(numVertices);
    std::vector<std::vector<int>> antPaths(numVertices, std::vector<int>(numVertices));
    std::vector<bool> visited(numVertices);
    std::vector<int> hamiltonianPath;
    int iteration = 0;

    int maxiter = numVertices * numVertices;

    while (iteration < maxiter) {
        for (int ant = 0; ant < numVertices; ++ant) {
            visited.assign(numVertices, false);
            antPaths[ant][0] = startVertex;
            visited[startVertex] = true;

            for (int i = 1; i < numVertices; ++i) {
                int currentVertex = antPaths[ant][i - 1];
                int nextVertex = getNextVertex(graph, pheromones, visited, currentVertex);

                if (nextVertex == -1) {
                    break;  // Все вершины посещены
                }

                antPaths[ant][i] = nextVertex;
                visited[nextVertex] = true;
            }
        }

        updatePheromones(pheromones, graph, antPaths);

        ++iteration;
    }

    double shortestPathLength = std::numeric_limits<double>::max();

    for (const auto& antPath : antPaths) {
        double pathLength = 0.0;

        for (size_t i = 0; i < antPath.size() - 1; ++i) {
            int source = antPath[i];
            int destination = antPath[i + 1];
            pathLength += graph[source].weight;
        }

        if (pathLength < shortestPathLength) {
            shortestPathLength = pathLength;
            hamiltonianPath = antPath;
        }
    }

    return hamiltonianPath;
}


void exercise9(Graph graph, int argc, const char* argv[])
{
    int start_vertex = -1;

    for (int i = 0; i < argc; ++i)
    {
        std::string key = argv[i];
        if (key == "-n") {
            start_vertex = std::stoi(argv[i + 1]);
            break;
        }
    }

    std::vector<Edge> newgraph = initializeGraph(graph);


    std::vector<int> answer = findHamiltonianCycle(graph, newgraph, start_vertex);
    if (answer.empty()) {
        std::cout << "Гамильтонов цикл не найден." << std::endl;
    }
    else {
        std::cout << "Hamiltonian cycle:" << std::endl;
        for (size_t i = 0; i < answer.size() - 1; ++i) {
            int source = answer[i];
            int destination = answer[i + 1];
            int weight = newgraph[source].weight;
            std::cout << source << " - " << destination << " " << weight << std::endl;
        }
    }
}