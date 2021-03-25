  /**
 * @file ant.cc
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.4
 * @date 2021-03-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "./ant.h"
#include "./expand.h"


void Ant::SetData(const int& x_pos, const int& y_pos, Directions direction,
         const Matrix<States>& orig_cells) {
  direction_ = direction;
  position_ = std::make_pair(x_pos - (-(orig_cells.size() / 2)),
                             y_pos - (-(orig_cells.at(0).size() / 2)));
  cells_ = orig_cells;
  h_limit_.superior = orig_cells.size() / 2;
  h_limit_.inferior = -(orig_cells.size() / 2);
  v_limit_.superior = orig_cells.at(0).size() / 2;
  v_limit_.inferior = -(orig_cells.at(0).size() / 2);
}


Ant& Ant::operator=(const Ant& second) {
  this->direction_ = second.direction_;
  this->h_limit_ = second.h_limit_;
  this->v_limit_ = second.v_limit_;
  this->position_ = second.position_;
  this->cells_ = second.cells_;
  this->infinity_ = second.infinity_;
  return *this;
}


void Ant::RecalculatePos() {
  if (cells_.size() != prev_cells_.size()) {
    if (cells_.at(position_.first) != prev_cells_.at(position_.first)) {
      position_ = std::make_pair(position_.first + kExpansion,
                                 position_.second);
    }
  }
  if (cells_.at(0).size() != prev_cells_.at(0).size()) {
    if (cells_.at(position_.second) != prev_cells_.at(position_.second)) {
      position_ = std::make_pair(position_.first,
                                 position_.second + kExpansion);
    }
  }
}
