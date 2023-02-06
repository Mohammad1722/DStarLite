/**
 * @file DstarLite.hpp
 * @author Mohammad Abdussalam (mohammadahmad01722@gmail.com)
 * @brief Implementation of D* Lite algorithm.
 * @see http://idm-lab.org/bib/abstracts/papers/aaai02b.pdf
 * @version 0.1
 * @date 2022-12-22
 */

#include "DStarLite.hpp"

/**
 * @brief Construct a new DStarLite::DStarLite object
 *
 * @param grid
 * @param start
 * @param goal
 */
DStarLite::DStarLite(const pair<int, int> &dim, const State &start, const State &goal) :
    _map {Grid(dim.first, vector<int>(dim.second, 0))}, s_start {start}, s_goal {goal},
    s_current {start}, _g {Grid(dim.first, vector<int>(dim.second, _INF_))},
    _rhs {Grid(dim.first, vector<int>(dim.second, _INF_))}
{
  rhs(s_goal) = 0;
  U.push(s_goal, {heuristic(s_start, s_goal), 0});

  computeShortestPath();
}

/**
 * @brief Computes the shortest path to the goal by assigning g-values to states
 * of interest.
 *
 */
void DStarLite::computeShortestPath()
{
  while (U.size())
  {
    auto [kOld, u] = U.top();
    if ((kOld >= calculateKey(s_start)) and (rhs(s_start) == g(s_start)))
      break;

    U.pop();
    auto kNew = calculateKey(u);

    if (kOld < kNew)
    {
      U.push(u, kNew);
      continue;
    }

    if (g(u) > rhs(u))
    {
      g(u) = rhs(u);
    }
    else
    {
      g(u) = _INF_;
      updateVertex(u);
    }
    for (const auto &neighbor: neighborStates(u))
    {
      updateVertex(neighbor);
    }
  }
}

/**
 * @brief Updates the RHS value of a state and insert it into the priority queue
 * if the state is inconsistent.
 *
 * @param s State
 */
void DStarLite::updateVertex(const State &s)
{
  if (s != s_goal)
  {
    rhs(s) = computeRHS(s);
  }

  if (g(s) != rhs(s))
  {
    U.update(s, calculateKey(s));
  }
  else
  {
    U.remove(s);
  }
}

/**
 * @brief Computes the RHS-value of a state.
 *
 * @param s State
 * @return int
 */
int DStarLite::computeRHS(const State &s) const
{
  int RHS = _INF_;
  for (const auto &neighbor: neighborStates(s))
  {
    RHS = std::min(RHS, g(neighbor) + cost(s, neighbor));
  }
  return RHS;
}

/**
 * @brief Calculates the key for a state.
 *
 * @param s State
 * @return Key
 */
Key DStarLite::calculateKey(const State &s) const
{
  auto min = std::min(g(s), rhs(s));
  return {min + heuristic(s_start, s) + km, min};
}

/**
 * @brief Calculate the heuristic for two States. (i.e., the estimated distance
 * between them)
 *
 * @param s1
 * @param s2
 * @return int
 */
int DStarLite::heuristic(const State &s1, const State &s2) const
{
  auto diff = s1 - s2;
  return std::abs(diff.first) + std::abs(diff.second);
  // return std::sqrt(std::pow(diff.first, 2) + std::pow(diff.second, 2));
}

/**
 * @brief Returns the cost of moving from s1 to s2.
 *
 * @param s1
 * @param s2
 * @return int
 */
int DStarLite::cost(const State &s1, const State &s2) const
{
  return (map(s1) or map(s2)) ? _INF_ : 1;
}

/**
 * @brief Returns a vector of neighbors of a State. A state s2 is considered
 * a neighbor to s1 if there is an action that can be taken while in s1 to move
 * directly to s2.
 *
 * @param s
 * @return vector<State>
 */
vector<State> DStarLite::neighborStates(const State &s) const
{
  vector<State> neighbors;
  for (const auto &a: actions)
  {
    auto nextState = s + a;

    if (nextState.first < 0 or nextState.second < 0
        or static_cast<size_t>(nextState.first) >= _map.size()
        or static_cast<size_t>(nextState.second) >= _map[0].size())
      continue;

    if (map(nextState))
      continue;

    neighbors.push_back(nextState);
  }
  return neighbors;
}

/**
 * @brief Returns an ordered vector of states from start to goal representing
 * the optimal path.
 *
 * @return vector<State>
 */
vector<State> DStarLite::getPath() const
{
  vector<State> path = {s_current};
  State s            = s_current;

  while (s != s_goal)
  {
    State s_next = peekNext(s);
    if (s_next == s)
      break;
    s = s_next;
    path.push_back(s);
  }

  return path;
}

/**
 * @brief Peek the next state on the optimal path.
 *
 * @param s
 * @return State
 */
State DStarLite::peekNext(const State &s) const
{
  if (s == s_goal)
    return s;

  State s_min = s;
  for (const auto &neighbor: neighborStates(s))
  {
    if (g(neighbor) < g(s_min))
    {
      s_min = neighbor;
    }
  }
  return s_min;
}

/**
 * @brief Move to the next state on the optimal path and update the internal
 * current state.
 *
 * @return State
 */
State DStarLite::moveNext()
{
  s_current = peekNext(s_current);
  return s_current;
}

/**
 * @brief Toggle the occupancy of a cell and recompute the shortest path.
 *
 * @param s
 */
void DStarLite::toggleCell(const State &s)
{
  // boundary checks
  if (s.first < 0 or s.second < 0 or static_cast<size_t>(s.first) >= _map.size()
      or static_cast<size_t>(s.second) >= _map[0].size())
    return;

  // current state and goal states cannot be occupied
  if (s == s_goal or s == s_current)
    return;

  km += heuristic(s_start, s_current);
  s_start = s_current;

  map(s) = 1 - map(s);
  updateVertex(s);
  for (const auto &neighbor: neighborStates(s))
  {
    updateVertex(neighbor);
  }

  computeShortestPath();
}

/**
 * @brief Adds an obstacle in a given state.
 *
 * @param u
 */
void DStarLite::blockCell(const State &u)
{
  if (map(u))
  {
    return;
  }
  else
  {
    toggleCell(u);
  }
}

/**
 * @brief Clears a state from obstacles.
 *
 * @param u
 */
void DStarLite::clearCell(const State &u)
{
  if (map(u))
  {
    toggleCell(u);
  }
  else
  {
    return;
  }
}

/**
 * @brief Update the occupied cells from a map.
 *
 * @param newMap
 */
void DStarLite::updateMap(const Grid &newMap)
{
  if (newMap.size() != _map.size() or newMap[0].size() != _map.size())
    return;

  for (size_t i = 0; i < _map.size(); i++)
  {
    for (size_t j = 0; j < _map.size(); j++)
    {
      if (_map[i][j] != newMap[i][j])
      {
        toggleCell({i, j});
      }
    }
  }
}

int DStarLite::g(const State &s) const
{
  return _g[s.first][s.second];
}

int &DStarLite::g(const State &s)
{
  return _g[s.first][s.second];
}

int DStarLite::rhs(const State &s) const
{
  return _rhs[s.first][s.second];
}

int &DStarLite::rhs(const State &s)
{
  return _rhs[s.first][s.second];
}

int DStarLite::map(const State &s) const
{
  return _map[s.first][s.second];
}

int &DStarLite::map(const State &s)
{
  return _map[s.first][s.second];
}
