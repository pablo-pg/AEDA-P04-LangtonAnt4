  /**
 * @file vector_t.h
 * @author Pablo Pérez González (alu0101318318@ull.edu.es)
 * @brief Programa que recrea el comportamioento de La Hormiga de Langton en C++
 * @version 0.2
 * @date 2021-03-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef VECTOR_T_H_
#define VECTOR_T_H_

#include <iostream>
#include <cassert>

enum ExpandDirection {exp_left, exp_right};


template <class T>
class vector_t: public std::vector {
 public:
  vector_t() {}
  vector_t(const int size = 0);
  vector_t(const int left, const int right);
  vector_t(const vector_t& second);
  vector_t(const int size, const T& element);
  ~vector_t();

  vector_t<T>& operator=(const vector_t<T>& second);

  void resize(const int);
  void clear();
  void expand(const ExpandDirection dir, const int expansion = 5);
  void push_back(const T& element);

  int size() const {return size_;}
  int left() const {return left_;}
  int right() const {return right_;}

  T& at(const int position_);
  T& operator[](const int position_);

  const T& at(const int position_) const;
  const T& operator[](const int position_) const;

  void print() {
    for (int i = 0; i < size_; ++i) {
      std::cout << v_[i] << " ";
    }
    std::cout << std::endl;
  }

 private:
  T* v_;
  int size_;
  int left_;
  int right_;
  int mid_point_;
  // int calculate_pos(const int& index);
  void copy_vect(const vector_t<T>& dummy);
};


template<class T>
vector_t<T>::vector_t(const int size) {
  size_ = size;
  left_ = 0;
  right_ = size;
  mid_point_ = size / 2;
  v_ = NULL;
  if (size_ != 0) {
    v_ = new T[size_];
  }
}


template<class T>
vector_t<T>::vector_t(const int left, const int right ) {
  size_ = right - left;
  left_ = left;
  right_ = right;
  mid_point_ = (right_ + left_) / 2;
  v_ = NULL;
  if ((size_ != 0) && (left_ < right_)) {
    v_ = new T[size_];
  }
}


template<class T>
vector_t<T>::~vector_t() {
  size_ = 0;
  left_ = 0;
  right_ = 0;
  mid_point_ = 0;
  if (v_ != NULL) {
    delete[] v_;
    v_ = NULL;
  }
}


template<class T>
vector_t<T>::vector_t(const vector_t<T>& second_vec) {
  *this = second_vec;
}


template<class T>
vector_t<T>& vector_t<T>::operator=(const vector_t<T>& second_vect) {
  if (v_ != NULL) {
    delete[] v_;
    v_ = NULL;
  }
  size_ = second_vect.size_;
  left_ = second_vect.left_;
  right_ = second_vect.right_;
  mid_point_ = second_vect.mid_point_;
  v_ = new T[second_vect.size()];
  for (int i = 0; i < size(); ++i)
    v_[i] = second_vect.v_[i];
  return *this;
}


template<class T>
void vector_t<T>::resize(const int new_size) {
  if (v_ != NULL) {
    delete[] v_;
    v_ = NULL;
  }
  size_ = new_size;
  right_ = left_ + new_size;
  mid_point_ = (left_ + right_) / 2;
  v_ = NULL;
  if (size_ != 0) {
    v_ = new T[new_size];
  }
}


template<class T>
void vector_t<T>::clear() {
  for (int i {0}; i < size_; ++i) {
    this->resize(0);
  }
}


template<class T>
void vector_t<T>::expand(const ExpandDirection dir, const int expansion) {
  if (expansion > 0) {
    if (dir == exp_right) {
      vector_t<T> dummy(left_, right_ + expansion);
      for (int i{0}; i < size_; ++i) {
        dummy.v_[i] = v_[i];
      }
      for (int j{0}; j < expansion; ++j) {
        dummy.at(right_ + j) = (T)0;
      }
      copy_vect(dummy);
    } else if (dir == exp_left) {
      vector_t<T> dummy(left_ - expansion, right_);
      for (int i{0}; i < expansion; ++i) {
        dummy.v_[i] = (T)0;
      }
      for (int j{0}; j < size_; ++j) {
        dummy.v_[expansion + j - 1] = v_[j];
      }
      copy_vect(dummy);
    }
  }
}


template<class T>
void vector_t<T>::push_back(const T& element) {
  expand(exp_right, 1);
  at(size_ - 1) = element;
}


template<class T>
T& vector_t<T>::at(const int position_) {
  if ((position_ > left_) && (position_ < right_)) {
    return v_[position_];
  }
}


template<class T>
T& vector_t<T>::operator[](const int position_) {
  if ((position_ > left_) && (position_ < right_)) {
    return v_[position_];
  }
}


template<class T>
const T& vector_t<T>::at(const int pos) const {
  if ((pos > left_) && (pos < right_)) {
    return v_[pos];
  }
}


template<class T>
const T& vector_t<T>::operator[](const int pos) const {
  if ((pos > left_) && (pos < right_)) {
    return v_[-(left_ - pos)];
  }
}


// template<class T>
// int vector_t<T>::calculate_pos(const int& index) {
//   int temp = left_ - index;
//   return -temp;
// }


template<class T>
void vector_t<T>::copy_vect(const vector_t<T>& second) {
  delete[] v_;
  v_ = NULL;
  v_ = new T[second.size_];
  for (int i{0}; i < second.size_; ++i) {
    v_[i] = second.v_[i];
  }
  size_ = second.size_;
  left_ = second.left_;
  right_ = second.right_;
  mid_point_ = second.mid_point_;
}


#endif      // VECTOR_T_H_
