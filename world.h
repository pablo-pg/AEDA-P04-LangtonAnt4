/**
 * @file world.h
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.1
 * @date 2021-03-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <deque>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

#include "./ant_a.h"
#include "./ant_b.h"


class World {
 public:
  World() {}
  virtual ~World() {}

  void Simulate(const int& paint_mode);

  virtual States _GetState(const int& x, const int& y) = 0;
  std::deque<Ant*> GetAnt() const {return ants_;}
  uint GetSteps() const {return kSteps_;}
  Matrix<States> GetMatrix() const {return cells_;}


  virtual void SetSize(const int& x, const int y) = 0;
  void SetAnt(const std::deque<Ant*>& ants) {ants_ = ants;}
  void SetSteps(const uint& steps) { kSteps_ = steps;}
  void UpdateMatrix(const Matrix<States>& new_matrix) {cells_ = new_matrix;}
  void UpdateAntPos(int x, int y) {
    x_ant_pos_ = x;
    y_ant_pos_ = y;
  }

 protected:
  void StandardPaint(const uint& step);
  void Paint(const uint& step);
  uint kSteps_;
  std::deque<Ant*> ants_;
  Matrix<States> cells_;  //< States definido en expand.h
  int x_ant_pos_;
  int y_ant_pos_;
  Limits h_limit_;
  Limits v_limit_;
};

#endif    // WORLD_H_
