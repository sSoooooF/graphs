#include "exercise9.h"
#include "graph.h"
#include <vector>
#include <climits>
#include <random>
#include <string>


const double alpha = 1.0; // феромоны
const double beta = 3.4; // видимость (эвристика)
const double p = 0.3; // испарение
const double q = 1.0; // Количество феромонов


// Функция для вывода маршрута
void printPath(const std::vector<int>& path, Graph graph) 
{
    int sum = 0;


    int size = path.size();
    for (int i = 0; i < size-1; ++i)
        if (graph.adjancency_matrix[path[i]][path[i + 1]] == 0)
        {
            std::cout << "Нет гамильтонова цикла\n";
            exit(0);
        }
    for (int i = 0; i < size-1; ++i) 
    {
        sum += graph.adjancency_matrix[path[i]][path[i + 1]];
        std::cout << path[i]+1 << " - " << path[i+1]+1 << " " << graph.adjancency_matrix[path[i]][path[i+1]] << std::endl;
    }

    std::cout << "\nИтоговый вес: " << sum << std::endl;
}


// Функция для расчета следующей вершины для посещения
int getNextVert(int currentVert, const std::vector<std::vector<double>>& visibility, const std::vector<std::vector<double>>& pheromones, const std::vector<bool>& visited) {
    int numVert = visibility.size();
    double sum = 0.0;

    std::vector<double> probabilities(numVert, 0.0);
    int numAvailableVert = 0;

    for (int i = 0; i < numVert; ++i) 
    {
        if (i == currentVert || visited[i]) {
            probabilities[i] = 0.0;
        }
        else {
            probabilities[i] = pow(pheromones[currentVert][i], alpha) * pow(visibility[currentVert][i], beta);
            sum += probabilities[i];
            numAvailableVert++;
        }
    }

    if (numAvailableVert == 0) {
        // Если нет, выбираем случайную непосещенную вершину
        for (int i = 0; i < numVert; ++i) {
            if (!visited[i]) {
                return i;
            }
        }
    }

    double random = (double)rand() / RAND_MAX;
    double cumulativeProbability = 0.0;
    for (int i = 0; i < numVert; ++i) 
    {
        if (i == currentVert)
            continue;

        cumulativeProbability += probabilities[i] / sum;

        if (random <= cumulativeProbability)
            return i;
    }

    return -1;  // что-то пошло не так
}


// Функция для обновления феромонов на ребрах
void updatePheromones(std::vector<std::vector<double>>& pheromones, const std::vector<std::vector<int>>& antPaths) {
    int numVert = pheromones.size();
    int numAnts = antPaths.size();

    for (int i = 0; i < numVert; ++i)
    {
        for (int j = 0; j < numVert; ++j) 
        {
            if (i == j)
                continue;

            pheromones[i][j] *= (1.0 - p);
        }
    }

    for (int k = 0; k < numAnts; ++k) 
    {
        int pathSize = antPaths[k].size();
        for (int i = 0; i < pathSize - 1; ++i) 
        {
            int from = antPaths[k][i];
            int to = antPaths[k][i + 1];
            pheromones[from][to] += q;
            pheromones[to][from] += q;
        }
    }
}

// Основная функция для поиска гамильтонова пути с использованием муравьиной колонии
std::vector<int> findHamiltonianPath(std::vector<std::vector<int>> graph, int startVertex) {
    int numVert = graph.size();

    std::vector<std::vector<double>> pheromones(numVert, std::vector<double>(numVert, 1.0));
    std::vector<std::vector<double>> visibility(numVert, std::vector<double>(numVert, 0.0));
    for (int i = 0; i < numVert; ++i) 
    {
        for (int j = 0; j < numVert; ++j) 
        {
            if (i == j) 
            {
                visibility[i][j] = 0.0;
            }
            else 
            {
                visibility[i][j] = 1.0 / graph[i][j];
            }
        }
    }

    std::vector<int> bestPath;
    double bestPathLength = std::numeric_limits<double>::max();

    for (int iter = 0; iter < numVert*numVert; ++iter) 
    {
        std::vector<std::vector<int>> antPaths;

        for (int ant = 0; ant < numVert; ++ant) 
        {
            std::vector<int> path;
            std::vector<bool> visited(numVert, false);
            int currentVert = startVertex;

            path.push_back(currentVert);
            visited[currentVert] = true;

            for (int i = 0; i < numVert - 1; ++i) 
            {
                int nextCity = getNextVert(currentVert, visibility, pheromones, visited);
                path.push_back(nextCity);
                visited[nextCity] = true;
                currentVert = nextCity;
            }
            // Добавляем начальную вершину в конец пути для формирования замкнутого цикла
            path.push_back(startVertex);

            antPaths.push_back(path);
        }

        // Находим лучший маршрут среди муравьев
        double minPathLength = std::numeric_limits<double>::max();
        int minPathIndex = -1;
        for (int i = 0; i < numVert; ++i) 
        {
            double pathLength = 0.0;
            int pathSize = antPaths[i].size();
            for (int j = 0; j < pathSize - 1; ++j) 
            {
                int from = antPaths[i][j];
                int to = antPaths[i][j + 1];
                pathLength += graph[from][to];
            }
            if (pathLength < minPathLength) 
            {
                minPathLength = pathLength;
                minPathIndex = i;
            }
        }

        // Обновляем лучший путь, если найден новый
        if (minPathLength < bestPathLength) 
        {
            bestPathLength = minPathLength;
            bestPath = antPaths[minPathIndex];
        }

        // Обновляем феромоны на ребрах
        updatePheromones(pheromones, antPaths);
    }

    return bestPath;
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

    std::vector<std::vector<int>> grap(graph.number_of_vertex, std::vector<int>(graph.number_of_vertex, 1000000));
    for (int i = 0; i < graph.number_of_vertex; ++i)
        for (int j = 0; j < graph.number_of_vertex; ++j)
            if (graph.adjancency_matrix[i][j] != 0)
                grap[i][j] = graph.adjancency_matrix[i][j];

    srand(time(0));
   

    std::vector<int> hamiltonPath = findHamiltonianPath(grap, start_vertex);

    std::cout << "Hamiltonian cycle:\n";
    printPath(hamiltonPath, graph);
}