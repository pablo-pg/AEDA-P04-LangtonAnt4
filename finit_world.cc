/**
 * @file finit_world.cc
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.3
 * @date 2021-03-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "./finit_world.h"


void FinitWorld::SetSize(const int& x, const int y) {
  cells_.resize(x);
  for (auto& columns : cells_) {
    columns.resize(y);
  }
  x_ant_pos_ = x / 2;
  y_ant_pos_ = y / 2;
}

