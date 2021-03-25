/**
 * @file ant_b.h
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.1
 * @date 2021-03-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ANT_B_H_
#define ANT_B_H_

#include "./ant.h"


class Ant_B : public Ant {
 public:
  virtual ~Ant_B() {}

  void Move();

 private:
  void Turn(const TurnDir& new_direction);
  void InfAdvance();
  void FinAdvance();
};


#endif  // ANT_B_H_
