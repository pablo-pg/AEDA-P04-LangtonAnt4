/**
 * @file ant_a.h
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.1
 * @date 2021-03-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ANT_A_H_
#define ANT_A_H_

#include "./ant.h"


class Ant_A : public Ant {
 public:
  virtual ~Ant_A() {}

  void Move();

 private:
  void Turn(const TurnDir& new_direction);
  void InfAdvance();
  void FinAdvance();
};


#endif  // ANT_A_H_
