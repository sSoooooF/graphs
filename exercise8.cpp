//#include "exercise8.h"
//#include "map.h"
//#include <functional>
//#include <iostream>
//
//int euclid(Cell* a, Cell* b) {
//    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
//}
//
//
//int chebyshev(Cell* a, Cell* b) {
//    return std::max(abs(a->x - b->x), abs(a->y - b->y));
//}
//
//
//int manhatton(Cell* a, Cell* b) {
//    return abs(a->x - b->x) + abs(a->y - b->y);
//}
//
//
//int zero(Cell* a, Cell* b) {
//    return 0;
//}
//
//
//struct CompareCells
//{
//    bool operator()(Cell* a, Cell* b)
//    {
//        return a->f() > b->f();
//    }
//};
//
//
//std::vector<Cell*> findPathAStar(Map& map, Cell* start, Cell* goal)
//{
//    std::priority_queue<Cell*, std::vector<Cell*>, CompareCells> openSet;
//    std::unordered_set<const Cell*> closedSet;
//
//    start->g = 0;
//    start->h = Cell::heuristic(start, goal);
//    openSet.push(start);
//
//    while (!openSet.empty())
//    {
//        Cell* current = openSet.top();
//        openSet.pop();
//
//        if (current == goal)
//        {
//            // Построение пути
//            std::vector<Cell*> path;
//            Cell* cell = current;
//            while (cell != nullptr)
//            {
//                path.push_back(cell);
//                cell = cell->parent;
//            }
//            std::reverse(path.begin(), path.end());
//            return path;
//        }
//
//        closedSet.insert(current);
//
//        std::vector<Cell*> neighbors = map.neighbors(*current);
//        for (Cell* neighbor : neighbors)
//        {
//            if (closedSet.find(neighbor) != closedSet.end())
//                continue;
//
//            int tentativeG = current->g + neighbor->weight;
//
//            bool neighborInOpenSet = false;
//            std::priority_queue<Cell*, std::vector<Cell*>, CompareCells> openSetCopy;
//            while (!openSet.empty())
//            {
//                Cell* openNeighbor = openSet.top();
//                openSet.pop();
//                if (openNeighbor == neighbor)
//                {
//                    neighborInOpenSet = true;
//                    break;
//                }
//                openSetCopy.push(openNeighbor);
//            }
//
//            if (tentativeG < neighbor->g || !neighborInOpenSet)
//            {
//                neighbor->parent = current;
//                neighbor->g = tentativeG;
//                neighbor->h = Cell::heuristic(neighbor, goal);
//
//                if (!neighborInOpenSet)
//                    openSetCopy.push(neighbor);
//
//                while (!openSetCopy.empty())
//                {
//                    openSet.push(openSetCopy.top());
//                    openSetCopy.pop();
//                }
//            }
//        }
//    }
//
//    // Не удалось найти путь
//    return {};
//}
//
//void exercise8(Map &map, int argc, const char* argv[])
//{
//    int startx,starty, endx, endy;
//    startx = starty = endx = endy = -1;
//
//    for (int i = 1; i < argc; ++i) 
//    {
//        std::string key = argv[i];
//        std::string value1 = argv[i + 1];
//        std::string value2 = argv[i + 2];
//
//        if (key == "-n") {
//            startx = std::stoi(value1);
//            starty = std::stoi(value2);
//        }
//
//        else if (key == "-d") {
//            endx = std::stoi(value1);
//            endy = std::stoi(value2);
//        }
//    }
//
//    Cell* start = map.get_cell(startx, starty);
//    Cell* end = map.get_cell(endx, endy);
//
//    Cell::heuristic = euclid;
//
//    std::vector<Cell*> path = findPathAStar(map, start, end);
//
//    if (!path.empty())
//    {
//        std::cout << "Маршрут найден:" << std::endl;
//        for (Cell* cell : path)
//        {
//            std::cout << "(" << cell->x << ", " << cell->y << ")" << std::endl;
//        }
//    }
//
//    Cell::heuristic = chebyshev;
//
//    path = findPathAStar(map, start, end);
//
//    if (!path.empty())
//    {
//        std::cout << "Маршрут найден:" << std::endl;
//        for (Cell* cell : path)
//        {
//            std::cout << "(" << cell->x << ", " << cell->y << ")" << std::endl;
//        }
//    }
//
//    Cell::heuristic = manhatton;
//
//    path = findPathAStar(map, start, end);
//
//    if (!path.empty())
//    {
//        std::cout << "Маршрут найден:" << std::endl;
//        for (Cell* cell : path)
//        {
//            std::cout << "(" << cell->x << ", " << cell->y << ")" << std::endl;
//        }
//    }
//}