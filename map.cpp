//#include "map.h"
//
////Map::Map(std::string filePath)
////{
////    file.open(filePath);
////    std::string line;
////
////    int x = 0;
////    while (std::getline(file, line)) 
////    {
////        int y = 0;
////        std::stringstream ss(line);
////        int weight;
////        std::vector<Cell> row;
////        while (ss >> weight) 
////        {
////            row.push_back({ x, y, weight });
////            y++;
////            totalCells++;
////        }
////        map.push_back(row);
////        x++;
////    }
////}
//
//std::vector<Cell*> Map::neighbors(Cell& c)
//{
//    std::vector<Cell*> neighbors;
//    int x = c.y;
//    int y = c.x;
//    int map_width = map[0].size();
//    int map_height = map.size();
//
//    if (x > 0)
//        neighbors.push_back(&map[y][x - 1]);
//
//    if (x < map_width - 1)
//        neighbors.push_back(&map[y][x + 1]);
//
//    if (y > 0)
//        neighbors.push_back(&map[y - 1][x]);
//
//    if (y < map_height - 1)
//        neighbors.push_back(&map[y + 1][x]);
//
//    return neighbors;
//}
//
//Cell::Cell(int x, int y, int weight) : x(x), y(y), weight(weight), g(INT_MAX), h(0), parent(nullptr)
//{
//}
