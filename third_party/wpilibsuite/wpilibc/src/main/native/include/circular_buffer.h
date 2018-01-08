/*----------------------------------------------------------------------------*/
/* Copyright (c) 2015-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <cstddef>
#include <vector>

namespace frc {

/**
 * This is a simple circular buffer so we don't need to "bucket brigade" copy
 * old values.
 */
template <class T>
class circular_buffer {
 public:
  explicit circular_buffer(size_t size);

  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* pointer;
  typedef size_t size_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;

  size_type size() const;
  T& front();
  const T& front() const;
  T& back();
  const T& back() const;
  void push_front(T value);
  void push_back(T value);
  T pop_front();
  T pop_back();
  void resize(size_t size);
  void reset();

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

 private:
  std::vector<T> m_data;

  // Index of element at front of buffer
  size_t m_front = 0;

  // Number of elements used in buffer
  size_t m_length = 0;

  size_t ModuloInc(size_t index);
  size_t ModuloDec(size_t index);
};

}  // namespace frc

#include "circular_buffer.inc"
