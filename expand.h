/**
 * @file expand.h
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.1
 * @date 2021-03-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef EXPAND_H_
#define EXPAND_H_

#include <vector>

enum Directions {left, leftUp, up, rightUp, right, downRight, down, downLeft};
enum States {black = 0, white};
enum ExpandDirection {exp_left, exp_right};
enum WorldType {finit_world, infinity_world};

struct Limits {
  int inferior;
  int superior;
};

const int kExpansion = 5;

template<typename T>
using Matrix = std::vector<std::vector<T>>;


Matrix<States> expandM(const ExpandDirection& dir, const Matrix<States>& matrix,
            const int expansion = kExpansion);


std::vector<States> expand(const ExpandDirection& dir, const std::vector<States>& vector,
            const int expansion = kExpansion);

#endif    // EXPAND_H_



