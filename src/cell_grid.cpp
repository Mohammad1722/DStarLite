#include "cell_grid.hpp"

CellGrid::CellGrid(pair<int, int> dim,
                   int cell_length,
                   int thickness,
                   pair<int, int> start,
                   pair<int, int> goal) :
    r(dim.first),
    c(dim.second), l(cell_length), th(thickness), start(start), goal(goal),
    grid(vector<vector<sf::RectangleShape>>(r, vector<sf::RectangleShape>(c)))
{
  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++)
    {
      sf::RectangleShape &rect = grid[i][j];
      rect.setSize(sf::Vector2f(l, l));
      rect.setPosition(sf::Vector2f((l + th) * j + th, (l + th) * i + th));
      rect.setOutlineThickness(th);
      rect.setOutlineColor(sf::Color::Black);
      rect.setFillColor(COLOR_CLEAR);
    }
  }
}

void CellGrid::toggleCell(pair<int, int> loc)
{
  if (grid[loc.first][loc.second].getFillColor() == COLOR_CLEAR)
    blockCell(loc);
  else
    clearCell(loc);
}

void CellGrid::blockCell(pair<int, int> loc)
{
  if (loc == start || loc == goal)
    return;

  grid[loc.first][loc.second].setFillColor(COLOR_BLOCKED);
}

void CellGrid::clearCell(pair<int, int> loc)
{
  // if (loc == start || loc == goal)
  //   return;

  grid[loc.first][loc.second].setFillColor(COLOR_CLEAR);
}

void CellGrid::setPath(vector<pair<int, int>> path)
{
  // remove previous path
  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++)
    {
      auto &cell = grid[i][j];
      if (cell.getFillColor() != COLOR_BLOCKED)
        cell.setFillColor(COLOR_CLEAR);
    }
  }

  for (auto &[i, j]: path)
  {
    auto &cell = grid[i][j];
    cell.setFillColor(COLOR_PATH);
  }
  auto &goal_cell = grid[goal.first][goal.second];
  goal_cell.setFillColor(COLOR_GOAL);

  auto &start_cell = grid[start.first][start.second];
  start_cell.setFillColor(COLOR_START);
}

void CellGrid::setStart(pair<int, int> s)
{
  start = s;
}

void CellGrid::setGoal(pair<int, int> s)
{
  goal = s;
}

void CellGrid::draw(sf::RenderWindow &window)
{
  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++)
    {
      auto &cell = grid[i][j];
      window.draw(cell);
    }
  }
}
