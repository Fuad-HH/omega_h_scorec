#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "internal.hpp"

namespace osh {

template <typename T>
INLINE T max2(T a, T b) {
  return (b > a) ? (b) : (a);
}
template <typename T>
INLINE T min2(T a, T b) {
  return (b < a) ? (b) : (a);
}
template <typename T>
INLINE void swap2(T& a, T& b) {
  T c = a;
  a = b;
  b = c;
}

}  // end namespace osh

#endif