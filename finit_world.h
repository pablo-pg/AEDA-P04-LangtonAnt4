/**
 * @file finit_world.h
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.3
 * @date 2021-03-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FINIT_WORLD_H_
#define FINIT_WORLD_H_

#include <iostream>
#include <vector>
#include <thread>
#include <iomanip>

#include "./world.h"


class FinitWorld : public World {
 public:
  virtual ~FinitWorld() {}

  void SetSize(const int& x, const int y);

  States _GetState(const int& x, const int& y) {return cells_.at(x).at(y);}
};

#endif    // FINIT_WORLD_H_
