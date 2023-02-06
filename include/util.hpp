/**
 * @file util.hpp
 * @author Mohammad Abdussalam (mohammadahmad01722@gmail.com)
 * @brief Helper and utility functions.
 * @version 0.1
 * @date 2022-12-22
 */

#ifndef __DSTARLITE_UTIL_HPP__
#define __DSTARLITE_UTIL_HPP__

#include <vector>
#include <utility>
#include <algorithm>

/**
 * @brief Overloading addition for `std::pair<T1, T2>`
 *
 * @tparam T1
 * @tparam T2
 * @param p1
 * @param p2
 * @return std::pair<T1, T2>
 */
template<typename T1, typename T2>
std::pair<T1, T2> operator+(const std::pair<T1, T2> &p1, const std::pair<T1, T2> &p2)
{
  return {p1.first + p2.first, p1.second + p2.second};
}

/**
 * @brief Overloading subtraction for `std::pair<T1, T2>`
 *
 * @tparam T1
 * @tparam T2
 * @param p1
 * @param p2
 * @return std::pair<T1, T2>
 */
template<typename T1, typename T2>
std::pair<T1, T2> operator-(const std::pair<T1, T2> &p1, const std::pair<T1, T2> &p2)
{
  return {p1.first - p2.first, p1.second - p2.second};
}

/**
 * @brief Overloading negation for `std::pair<T1, T2>`
 *
 * @tparam T1
 * @tparam T2
 * @param p
 * @return std::pair<T1, T2>
 */
template<typename T1, typename T2> std::pair<T1, T2> operator-(const std::pair<T1, T2> &p)
{
  return {-p.first, -p.second};
}

/**
 * @brief Return the index of the minimum element in a vector
 *
 * @tparam T
 * @param v
 * @return size_t
 */
template<typename T> size_t arg_min(std::vector<T> v)
{
  return std::min_element(v.begin(), v.end()) - v.begin();
}

#endif /* __DSTARLITE_UTIL_HPP__ */
