/**
 * @file PriorityQueue.hpp
 * @author Mohammad Abdussalam (mohammadahmad01722@gmail.com)
 * @brief Simple priority queue based on STL
 * @version 0.1
 * @date 2022-12-22
 */

#ifndef __DSTARLITE_PRIORITYQUEUE_HPP__
#define __DSTARLITE_PRIORITYQUEUE_HPP__

#include <vector>
#include <utility>
#include <algorithm>

using std::make_heap;
using std::pair;
using std::pop_heap;
using std::push_heap;
using std::vector;

/**
 * @brief Priority Queue container class. Adds "remove element by value"
 * function to the STL implementation
 *
 * @tparam Tp The type of the priority
 * @tparam Te The type of elements in the queue
 */
template<class Tp, class Te> class PriorityQueue
{
 public:
  /**
   * @brief Peek the value of the top element and return a key-value pair.
   *
   * @return pair<Tp, Te> {priority, element}
   */
  pair<Tp, Te> top() const
  {
    return data.front();  // return {priority, elem} pair
  }

  /**
   * @brief Peek the key of the top element.
   *
   * @return Tp Priority
   */
  Tp topKey() const
  {
    return data.front().first;  // return priority only;
  }

  /**
   * @brief Returns the number of elements currently in the container.
   *
   * @return int
   */
  int size() const
  {
    return data.size();
  }

  /**
   * @brief Returns true if the container is empty.
   *
   * @return true
   * @return false
   */
  bool empty() const
  {
    return data.empty();
  }

  /**
   * @brief Pops the top element and returns a key-value pair.
   *
   * @return pair<Tp, Te> {priority, element}
   */
  pair<Tp, Te> pop()
  {
    std::pop_heap(data.begin(), data.end(), std::greater<pair<Tp, Te>> {});
    pair<Tp, Te> temp = data.back();
    data.pop_back();
    return temp;
  }

  /**
   * @brief Pushs an element into the container
   *
   * @param elem
   * @param priority
   */
  void push(const Te &elem, const Tp &priority)
  {
    data.push_back({priority, elem});
    std::push_heap(data.begin(), data.end(), std::greater<pair<Tp, Te>> {});
  }

  /**
   * @brief Updates the priority of a given element if exists.
   * Otherwise, insert it.
   *
   * @param elem
   * @param priority
   */
  void update(const Te &elem, const Tp &priority)
  {
    auto &&it = find(elem);
    if (it == data.end())
    {
      push(elem, priority);
      return;
    }

    auto &[p, item] = *it;

    if (priority == p)
      return;
    p = priority;
    std::make_heap(data.begin(), data.end(), std::greater<pair<Tp, Te>> {});
  }

  /**
   * @brief Remove an element by value from the container.
   *
   * @param elem
   */
  void remove(const Te &elem)
  {
    auto &&it = find(elem);
    if (it == data.end())
      return;

    data.erase(it);
    std::make_heap(data.begin(), data.end(), std::greater<pair<Tp, Te>> {});
  }

 private:
  vector<pair<Tp, Te>> data;

  /**
   * @brief Returns an iterator to the element in the underlying vector.
   *
   * @param elem
   * @return vector<pair<Tp, Te>>::iterator
   */
  typename vector<pair<Tp, Te>>::iterator find(const Te &elem)
  {
    for (auto it = data.begin(); it != data.end(); it++)
    {
      if (elem == it->second)
      {
        return it;
      }
    }
    return data.end();
  }
};

#endif /* __DSTARLITE_PRIORITYQUEUE_HPP__ */
