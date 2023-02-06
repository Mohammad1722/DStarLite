#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <utility>
#include <algorithm>
#include <vector>

#include "DStarLite.hpp"
#include "cell_grid.hpp"

#define r 30  // number of rows in the grid
#define c 40  // number of cols in the grid
#define l 20  // length of grid cell in pixels
#define th 2  // thickness of cell outline in pixels

const std::pair<int, int> START = {r / 2, c / 4};
const std::pair<int, int> GOAL  = {r / 2, 3 * c / 4};

constexpr int w = th + c * (l + th);  // window width
constexpr int h = th + r * (l + th);  // window height

std::pair<int, int> mouse_get_cell(const sf::RenderWindow &window)
{
  auto mouse_pos = sf::Mouse::getPosition(window);
  int i          = (mouse_pos.y - 0.5 * th) / (l + th);
  int j          = (mouse_pos.x - 0.5 * th) / (l + th);

  i = std::clamp(i, 0, r - 1);
  j = std::clamp(j, 0, c - 1);

  return {i, j};
}

int main(void)
{
  DStarLite dsl({r, c}, START, GOAL);
  CellGrid cg({r, c}, l, th, START, GOAL);

  // create the window
  sf::RenderWindow window(sf::VideoMode(w, h), "D*-Lite", sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(24);
  window.clear(sf::Color::Green);

  // run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        auto loc = mouse_get_cell(window);

        cg.blockCell(loc);
        dsl.blockCell(loc);
      }

      if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
      {
        auto loc = mouse_get_cell(window);

        cg.clearCell(loc);
        dsl.clearCell(loc);
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
      {
        for (int i = 0; i < r; i++)
        {
          for (int j = 0; j < c; j++)
          {
            cg.clearCell({i, j});
            dsl.clearCell({i, j});
          }
        }
      }
    }

    cg.setPath(dsl.getPath());
    cg.draw(window);

    // end the current frame
    window.display();
  }

  return 0;
}
