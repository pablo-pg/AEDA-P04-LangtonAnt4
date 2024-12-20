  /**
 * @file ant.h
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.4
 * @date 2021-03-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ANT_H_
#define ANT_H_

#include <iostream>
#include <map>
#include <deque>
#include <string>
#include <utility>
#include <vector>

#include "./expand.h"

struct KnowAnt {
  bool is = false;
  Directions direction;
  int h_pos;
  int v_pos;
  uint list_pos;
};


class Ant {
 public:
  Ant() {}
  virtual ~Ant() {}

  virtual void Move() = 0;

  uint GetHPos() const {return position_.first;}
  uint GetVPos() const {return position_.second;}
  int GetHInfLimit() const {return h_limit_.inferior;}
  int GetVInfLimit() const {return v_limit_.inferior;}
  Directions GetDirection() const {return direction_;}
  Matrix<States> GetCell() const {return cells_;}

  void SetData(const int& x_pos, const int& y_pos, Directions direction,
               const Matrix<States>&orig_cells);
  void SetPrevMatrix(const Matrix<States> matrix) { prev_cells_ = matrix;}
  void SetMatrix(const Matrix<States> matrix) { cells_ = matrix;}
  void SetLimits(const Limits& h, const Limits& v) {
    h_limit_ = h;
    v_limit_ = v;
  }
  void SetTypeWorld(const WorldType& type) {infinity_ = type;}

  Ant& operator=(const Ant& second);

 protected:
  virtual void Turn(const TurnDir& new_direction) = 0;
  virtual void InfAdvance() = 0;
  virtual void FinAdvance() = 0;
  void RecalculatePos();
  Directions direction_;
  Limits h_limit_;
  Limits v_limit_;
  std::pair<int, int> position_;
  Matrix<States> cells_;
  Matrix<States> prev_cells_;
  WorldType infinity_;
};

#endif    // ANT_H_
