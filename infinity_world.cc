  /**
 * @file infinity_world.cc
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.3
 * @date 2021-03-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "./infinity_world.h"
#include "./expand.h"


void InfinityWorld::SetSize(const int& x, const int y) {
  cells_.resize(x);
  for (size_t i {0}; i < cells_.size(); ++i) {
    cells_.at(i).resize(y);
  }
  x_ant_pos_ = 0;
  y_ant_pos_ = 0;
  if (x % 2 == 0) {
    h_limit_ = {-(x / 2), ((x / 2) - 1)};
  } else {
    h_limit_ = {-(x / 2), (x / 2)};
  }
  if (y % 2 == 0) {
    v_limit_ = {-(y / 2), ((y / 2) - 1)};
  } else {
    v_limit_ = {-(y / 2), (y / 2)};
  }
}


States InfinityWorld::_GetState(const int& x, const int& y) {
  if (x < h_limit_.superior && x > h_limit_.inferior) {
    if ((y > v_limit_.inferior)
        && (y < v_limit_.superior)) {
      return cells_.at(-(h_limit_.inferior - x)).at(-(v_limit_.inferior - y));
    } else if ((y > v_limit_.inferior)
        && (y > v_limit_.superior)) {
      for (size_t i {0}; i < cells_.size(); ++i) {
        expand(exp_right, cells_.at(i));
      }
      return cells_.at(-(h_limit_.inferior - x)).at(-(h_limit_.inferior - y));
    } else if ((y < v_limit_.inferior)
        && (y < v_limit_.superior)) {
      for (size_t i {0}; i < cells_.size(); ++i) {
        expand(exp_left, cells_.at(i));
      }
      return cells_.at(-(h_limit_.inferior - x)).at(-(h_limit_.inferior - y));
    }
  } else if (x > h_limit_.inferior && x > h_limit_.superior) {
    int origin_size = cells_.size();
    cells_ = expandM(exp_right, cells_);
    for (int i {0}; i < kExpansion; ++i) {
      cells_.at(i + origin_size).resize(cells_.at(0).size());
    }
    _GetState(x, y);
  } else if (x < h_limit_.inferior && x < h_limit_.superior) {
    cells_ = expandM(exp_left, cells_);
    for (int i {0}; i < kExpansion; ++i) {
      cells_.at(i).resize(cells_.at(kExpansion).size());
    }
    _GetState(x, y);
  }
  return cells_.at(-(h_limit_.inferior - x)).at(-(h_limit_.inferior - y));
}




