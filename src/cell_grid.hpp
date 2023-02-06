#ifndef __CELL_GRID_HPP__
#define __CELL_GRID_HPP__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>

#define COLOR_CLEAR sf::Color(255, 255, 255)
#define COLOR_BLOCKED sf::Color(0, 0, 0)
#define COLOR_PATH sf::Color(255, 87, 51)
#define COLOR_START sf::Color(32, 178, 170)
#define COLOR_GOAL sf::Color(34, 139, 34)

using std::pair;
using std::vector;

class CellGrid
{
 public:
  CellGrid(pair<int, int> dim, int l, int th, pair<int, int> start, pair<int, int> goal);
  void toggleCell(pair<int, int> loc);
  void blockCell(pair<int, int> loc);
  void clearCell(pair<int, int> loc);
  void setPath(vector<pair<int, int>> path);
  void setStart(pair<int, int> s);
  void setGoal(pair<int, int> s);

  void draw(sf::RenderWindow &window);

 private:
  int r, c, l, th;
  pair<int, int> start, goal;
  vector<vector<sf::RectangleShape>> grid;
};

#endif /* __CELL_GRID_HPP__ */
