/**
 * @file expand.cc
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.1
 * @date 2021-03-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "./expand.h"



Matrix<States>expandM(const ExpandDirection& dir, const Matrix<States>& matrix,
            const int expansion) {
  Matrix<States> dummy;
  dummy.resize(matrix.size() + expansion);
  for (auto& element : dummy) {
    element.resize(matrix.at(0).size());
  }
  if (dir == exp_right) {
    for (size_t i {0}; i < matrix.size(); ++i) {
      dummy.at(i) = matrix.at(i);
    }
  } else if (dir == exp_left) {
    for (size_t i {0}; i < matrix.size(); ++i) {
      dummy.at(expansion + i) = matrix.at(i);
    }
  }
  return dummy;
}


std::vector<States> expand(const ExpandDirection& dir,
        const std::vector<States>& vector, const int expansion) {
  std::vector<States> dummy;
  dummy.resize(vector.size() + expansion);
  if (dir == exp_right) {
    for (size_t i {0}; i < vector.size(); ++i) {
      dummy.at(i) = vector.at(i);
    }
  } else if (dir == exp_left) {
    for (size_t i {0}; i < vector.size(); ++i) {
      dummy.at(expansion + i) = vector.at(i);
    }
  }
  return dummy;
}


