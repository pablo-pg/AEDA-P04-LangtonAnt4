  /**
 * @file universe.h
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.2
 * @date 2021-03-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef UNIVERSE_H_
#define UNIVERSE_H_

#include <deque>
#include <exception>
#include <iostream>
#include <system_error>

#include "./ant_a.h"
#include "./infinity_world.h"
#include "./finit_world.h"

class Universe {
 public:
  Universe();
  Universe(World& world, const WorldType& type, const std::deque<Ant*>& ants);
  ~Universe() {}

  void Simulate(const int& paint_mode);

 private:
  void StandardPaint(const uint& step);
  void Paint(const uint& step);
  KnowAnt AreAnts(const uint& i, const uint& j);
  uint steps_;
  std::deque<Ant*> ant_list_;
  World* world_;
  WorldType infinity_;
  Matrix<States> cells_;
};

#endif    // UNIVERSE_H_
