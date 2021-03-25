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

const Directions start_direction = up;


Ant::Ant() {
  direction_ = start_direction;
  position_ = std::make_pair(0, 0);
  h_limit_ = {0, 0};
  v_limit_ = {0, 0};
  cells_.clear();
  infinity_ = finit_world;
}


Ant::~Ant() {
  direction_ = start_direction;
  cells_.clear();
}


Ant::Ant(const Ant& second) {
  this->cells_ = second.cells_;
  this->direction_ = second.direction_;
  this->h_limit_ = second.h_limit_;
  this->v_limit_ = second.v_limit_;
  this->position_ = second.position_;
  this->infinity_ = second.infinity_;
}


Ant::Ant(const int& x_pos, const int& y_pos, Directions direction,
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


Ant::Ant(const uint& size, const Matrix<States>& orig_cells,
         const WorldType& infinity) {
  direction_ = start_direction;
  position_ = std::make_pair(size / 2, size / 2);
  cells_ = orig_cells;
  h_limit_.superior = size / 2;
  h_limit_.inferior = -(size / 2);
  v_limit_.superior = size / 2;
  v_limit_.inferior = -(size / 2);
  infinity_ = infinity;
}


Ant::Ant(const uint& h_size, const uint& v_size,
         const Matrix<States>& orig_cells, const WorldType& infinity) {
  direction_ = start_direction;
  position_ = std::make_pair(h_size / 2, v_size / 2);
  cells_ = orig_cells;
  h_limit_.superior = h_size / 2;
  h_limit_.inferior = -(h_size / 2);
  v_limit_.superior = v_size / 2;
  v_limit_.inferior = -(v_size / 2);
  infinity_ = infinity;
}


void Ant::Move() {
  if (infinity_ == 1) {
    RecalculatePos();
    if (cells_.at(position_.first).at(position_.second) == black) {
      cells_.at(position_.first).at(position_.second) = white;
      Turn(turn_left);
      InfAdvance();
    } else if (cells_.at(position_.first).at(position_.second) == white) {
      cells_.at(position_.first).at(position_.second) = black;
      Turn(turn_right);
      InfAdvance();
    }
  } else {
    if (cells_.at(position_.first).at(position_.second) == black) {
      cells_.at(position_.first).at(position_.second) = white;
      Turn(turn_left);
      FinAdvance();
    } else if (cells_.at(position_.first).at(position_.second) == white) {
      cells_.at(position_.first).at(position_.second) = black;
      Turn(turn_right);
      FinAdvance();
    }
  }
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


void Ant::Turn(const TurnDir& new_direction) {
  if (new_direction == turn_left) {
    switch (direction_) {
    case left:
      direction_ = downLeft;
      break;
    case downLeft:
      direction_ = down;
      break;
    case down:
      direction_ = downRight;
      break;
    case downRight:
      direction_ = right;
      break;
    case right:
      direction_ = rightUp;
      break;
    case rightUp:
      direction_ = up;
      break;
    case up:
      direction_ = leftUp;
      break;
    case leftUp:
      direction_ = left;
      break;
    default:
      direction_ = up;
      break;
    }
  } else if (new_direction == turn_right) {
    switch (direction_) {
    case left:
      direction_ = leftUp;
      break;
    case leftUp:
      direction_ = up;
      break;
    case up:
      direction_ = rightUp;
      break;
    case rightUp:
      direction_ = right;
      break;
    case right:
      direction_ = downRight;
      break;
    case downRight:
      direction_ = down;
      break;
    case down:
      direction_ = downLeft;
      break;
    case downLeft:
      direction_ = left;
      break;
    default:
      direction_ = up;
      break;
    }
  }
}


void Ant::InfAdvance() {
  switch (direction_) {
  case up:
    position_ = std::make_pair(position_.first, position_.second + 1);
    if (position_.second == static_cast<int>(cells_.at(0).size()) - 1) {
      for (size_t i {0}; i < cells_.size(); ++i) {
        cells_ .at(i) = expand(exp_right, cells_.at(i));
      }
      v_limit_.superior += kExpansion;
    }
    break;
  case right:
    position_ = std::make_pair(position_.first + 1, position_.second);
    if ((size_t)position_.first == cells_.size() - 1) {
       cells_ = expandM(exp_right, cells_);
      h_limit_.superior += kExpansion;
    }
    break;
  case down:
    position_ = std::make_pair(position_.first, position_.second - 1);
    if (position_.second == 0) {
      for (size_t i {0}; i < cells_.size(); ++i) {
        cells_ .at(i) = expand(exp_left, cells_.at(i));
      }
      v_limit_.inferior -= kExpansion;
      position_ = std::make_pair(position_.first, position_.second+kExpansion);
    }
    break;
  case left:
    position_ = std::make_pair(position_.first - 1, position_.second);
    if (position_.first == 0) {
      cells_ = expandM(exp_left, cells_);
      h_limit_.inferior -= kExpansion;
      position_ = std::make_pair(position_.first+kExpansion, position_.second);
    }
    break;
  /// DIAGONALES
  case leftUp:
    position_ = std::make_pair(position_.first - 1, position_.second + 1);
    if ((position_.first == 0)
                && ((size_t)position_.second >= cells_.at(0).size() - 1)) {
      h_limit_.inferior -= kExpansion;
      v_limit_.superior += kExpansion;
      position_ = std::make_pair(position_.first+kExpansion, position_.second);
      cells_ = expandM(exp_left, cells_);
      for (size_t i {0}; i < cells_.size(); ++i) {
        cells_ .at(i) = expand(exp_right, cells_.at(i));
      }
    } else if (position_.first == 0) {
      cells_ = expandM(exp_left, cells_);
      h_limit_.inferior -= kExpansion;
      position_ = std::make_pair(position_.first+kExpansion, position_.second);
    } else if ((size_t)position_.second >= cells_.at(0).size() - 1) {
      v_limit_.superior += kExpansion;
      for (size_t i {0}; i < cells_.size(); ++i) {
        cells_ .at(i) = expand(exp_right, cells_.at(i));
      }
    }
    break;
  case rightUp:
    position_ = std::make_pair(position_.first + 1, position_.second + 1);
    if ((size_t)position_.first == cells_.size() - 1) {
       cells_ = expandM(exp_right, cells_);
      h_limit_.superior += kExpansion;
    } else if ((size_t)position_.second >= cells_.at(0).size() - 1) {
      for (size_t i {0}; i < cells_.size(); ++i) {
        cells_ .at(i) = expand(exp_right, cells_.at(i));
      }
      v_limit_.superior += kExpansion;
    } else if (((size_t)position_.first >= cells_.at(0).size() - 1)
                && ((size_t)position_.second >= cells_.at(0).size() - 1)) {
       cells_ = expandM(exp_right, cells_);
        v_limit_.superior += kExpansion;
        h_limit_.superior += kExpansion;
      for (size_t i {0}; i < cells_.size(); ++i) {
        cells_ .at(i) = expand(exp_right, cells_.at(i));
      }
    }
    break;
  case downRight:
    position_ = std::make_pair(position_.first + 1, position_.second - 1);
      if ((size_t)position_.first == cells_.size() - 1) {
         cells_ = expandM(exp_right, cells_);
        h_limit_.inferior += kExpansion;
    } else if (position_.second == 0) {
      for (size_t i {0}; i < cells_.size(); ++i) {
        cells_ .at(i) = expand(exp_left, cells_.at(i));
      }
      position_ = std::make_pair(position_.first, position_.second+kExpansion);
      v_limit_.inferior -= kExpansion;
    } else if (((size_t)position_.first == cells_.size() - 1)
              && (position_.second == 0)) {
      cells_ = expandM(exp_right, cells_);
      v_limit_.inferior -= kExpansion;
      h_limit_.inferior += kExpansion;
      position_ = std::make_pair(position_.first, position_.second+kExpansion);
      for (size_t i {0}; i < cells_.size(); ++i) {
        cells_ .at(i) = expand(exp_left, cells_.at(i));
      }
    }
    break;
  case downLeft:
    position_ = std::make_pair(position_.first - 1, position_.second - 1);
    if ((position_.first == 0) && (position_.second == 0)) {
      v_limit_.inferior -= kExpansion;
      h_limit_.inferior -= kExpansion;
      position_ = std::make_pair(position_.first+kExpansion, position_.second);
      position_ = std::make_pair(position_.first, position_.second+kExpansion);
       cells_ = expandM(exp_left, cells_);
      for (size_t i {0}; i < cells_.size(); ++i) {
        cells_ .at(i) = expand(exp_left, cells_.at(i));
      }
    } else if (position_.first == 0) {
      cells_ = expandM(exp_left, cells_);
      h_limit_.inferior -= kExpansion;
      position_ = std::make_pair(position_.first+kExpansion, position_.second);
    } else if (position_.second == 0) {
      for (size_t i {0}; i < cells_.size(); ++i) {
        cells_ .at(i) = expand(exp_left, cells_.at(i));
      }
      v_limit_.inferior -= kExpansion;
      position_ = std::make_pair(position_.first, position_.second+kExpansion);
    }
    break;
  default:
    break;
  }
}


void Ant::FinAdvance() {
  switch (direction_) {
  case up:
    if (position_.second >= cells_.at(0).size() - 1) {
      position_ = std::make_pair(position_.first, 0);
    } else {
      position_ = std::make_pair(position_.first, position_.second + 1);
    }
    break;
  case right:
    if (position_.first == cells_.size() - 1) {
      position_ = std::make_pair(0, position_.second);
    } else {
      position_ = std::make_pair(position_.first + 1, position_.second);
    }
    break;
  case down:
    if (position_.second == 0) {
      position_ = std::make_pair(position_.first, cells_.at(0).size() - 1);
    } else {
      position_ = std::make_pair(position_.first, position_.second - 1);
    }
    break;
  case left:
    if (position_.first == 0) {
      position_ = std::make_pair(cells_.size() - 1, position_.second);
    } else {
      position_ = std::make_pair(position_.first - 1, position_.second);
    }
    break;
  /// DIAGONALES
  case leftUp:
    if ((position_.first == 0) && (position_.second == cells_.at(0).size() - 1)) {
      position_ = std::make_pair(cells_.size() - 1, 0);
    } else if (position_.first == 0) {
      position_ = std::make_pair(cells_.size() - 1, position_.second + 1);
    } else if (position_.second == cells_.at(0).size() - 1) {
      position_ = std::make_pair(position_.first - 1, 0);
    } else {
      position_ = std::make_pair(position_.first - 1, position_.second + 1);
    }
    break;
  case rightUp:
    if ((position_.first == cells_.size() - 1) && (position_.second == cells_.at(0).size() - 1)) {
      position_ = std::make_pair(0, 0);
    } else if (position_.first == cells_.size() - 1) {
      position_ = std::make_pair(0, position_.second + 1);
    } else if (position_.second == cells_.at(0).size() - 1) {
      position_ = std::make_pair(position_.first + 1, 0);
    } else {
      position_ = std::make_pair(position_.first + 1, position_.second + 1);
    }
    break;
  case downRight:
    if ((position_.first == cells_.size() - 1) && (position_.second == 0)) {
      position_ = std::make_pair(0, cells_.at(0).size() - 1);
    } else if (position_.first == cells_.size() - 1) {
      position_ = std::make_pair(0, position_.second - 1);
    } else if (position_.second == 0) {
      position_ = std::make_pair(position_.first + 1, cells_.at(0).size() - 1);
    } else {
      position_ = std::make_pair(position_.first + 1, position_.second - 1);
    }
    break;
  case downLeft:
    if ((position_.first == 0) && (position_.second == 0)) {
      position_ = std::make_pair(cells_.size() - 1, cells_.at(0).size() - 1);
    } else if (position_.first == 0) {
      position_ = std::make_pair(cells_.size() - 1, position_.second - 1);
    } else if (position_.second == 0) {
      position_ = std::make_pair(position_.first - 1, cells_.at(0).size() - 1);
    } else {
      position_ = std::make_pair(position_.first - 1, position_.second - 1);
    }
    break;
  default:
    break;
  }
}


void Ant::RecalculatePos() {
  if (cells_.size() != prev_cells_.size()) {
    if (cells_.at(position_.first) != prev_cells_.at(position_.first)) {
      position_ = std::make_pair(position_.first + kExpansion, position_.second);
    }
  }
  if (cells_.at(0).size() != prev_cells_.at(0).size()) {
    if (cells_.at(position_.second) != prev_cells_.at(position_.second)) {
      position_ = std::make_pair(position_.first, position_.second + kExpansion);
    }
  }
}
