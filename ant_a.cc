/**
 * @file ant_a.cc
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.1
 * @date 2021-03-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "./ant_a.h"


void Ant_A::Move() {
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


void Ant_A::Turn(const TurnDir& new_direction) {
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



void Ant_A::InfAdvance() {
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


void Ant_A::FinAdvance() {
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
    if ((position_.first == 0)
        && (position_.second == cells_.at(0).size() - 1)) {
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
    if ((position_.first == cells_.size() - 1)
        && (position_.second == cells_.at(0).size() - 1)) {
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

