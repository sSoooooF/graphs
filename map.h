//#pragma once
//#include <fstream>
//#include <vector>
//#include <string>
//#include <sstream>
//#include <functional>
//
//struct Cell
//{
//    int x;
//    int y;
//    int weight;
//    int g;
//    int h;
//    Cell* parent;
//
//    static std::function<int(Cell*, Cell*)> heuristic;
//
//    Cell(int x, int y, int weight);
//
//    int f()
//    {
//        return g + h;
//    }
//};
//
//class Map
//{
//private:
//    std::fstream file;
//    std::vector<std::vector<Cell>> map;
//    int totalCells = 0;
//
//public:
//    int visitedCells = 0;
//
//    Map(std::string filePath)
//        {
//    file.open(filePath);
//    std::string line;
//
//    int x = 0;
//    while (std::getline(file, line)) 
//    {
//        int y = 0;
//        std::stringstream ss(line);
//        int weight;
//        std::vector<Cell> row;
//        while (ss >> weight) 
//        {
//            row.push_back({ x, y, weight });
//            y++;
//            totalCells++;
//        }
//        map.push_back(row);
//        x++;
//    }
//};
//
//    static int heuristicDistance(Cell* a, Cell* b) {
//        return Cell::heuristic(a, b);
//    }
//
//    std::vector<Cell*> neighbors(Cell& c);
//
//    int get_height(Cell c)
//    {
//        return c.weight;
//    }
//
//    Cell* get_cell(int x, int y)
//    {
//        return &map[x][y];
//    }
//};