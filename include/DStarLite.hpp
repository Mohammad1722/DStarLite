/**
 * @file DstarLite.hpp
 * @author Mohammad Abdussalam (mohammadahmad01722@gmail.com)
 * @brief Implementation of D* Lite algorithm.
 * @see http://idm-lab.org/bib/abstracts/papers/aaai02b.pdf
 * @version 0.1
 * @date 2022-12-22
 */

#ifndef __DSTARLITE_DSTARLITE_HPP__
#define __DSTARLITE_DSTARLITE_HPP__

#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

#include "PriorityQueue.hpp"
#include "util.hpp"

#define _INF_ 0x2fffffff  // slightly less than INT32_MAX to avoid overflows

typedef std::pair<int, int> State;
typedef std::pair<int, int> Key;
typedef std::vector<vector<int>> Grid;

class DStarLite
{
 public:
  DStarLite(const pair<int, int> &dim, const State &start, const State &goal);
  vector<State> getPath() const;
  State peekNext(const State &s) const;
  State moveNext();
  void toggleCell(const State &u);
  void blockCell(const State &u);
  void clearCell(const State &u);
  void updateMap(const Grid &newMap);

 private:
  Grid _map;
  State s_start {0, 0};    // s_start is the robot start location in the current plan
  State s_goal {0, 0};     // s_goal is the goal location
  State s_current {0, 0};  // s_current is the current robot location
  Grid _g;    // The g_value is an estimate of the distance to goal distance from each location
  Grid _rhs;  // The rhs values are one-step lookahead values based on the g-values
  PriorityQueue<Key, State> U;
  int km {0};
  vector<State> actions {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  // vector<State> actions {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

  void computeShortestPath();
  void updateVertex(const State &u);
  int computeRHS(const State &u) const;
  Key calculateKey(const State &s) const;
  int heuristic(const State &s1, const State &s2) const;
  int cost(const State &s1, const State &s2) const;
  vector<State> neighborStates(const State &s) const;

  int map(const State &s) const;
  int &map(const State &s);
  int g(const State &s) const;
  int &g(const State &s);
  int rhs(const State &s) const;
  int &rhs(const State &s);
};

#endif /* __DSTARLITE_DSTARLITE_HPP__ */
