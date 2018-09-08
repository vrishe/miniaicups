#pragma once

#ifndef VRISHE_INTERPOLATION_H_
#define VRISHE_INTERPOLATION_H_

#include <functional>

#define LERP(x, x1, x2, f1, f2)  \
  (((x-x1)*f2+(x2-x)*f1)/(x2-x1))
#define BLERP(x, y, x1, y1, x2, y2, f11, f12, f21, f22)  \
  (((y-y1)*((x-x1)*f22+(x2-x)*f12)                       \
      +(y2-y)*((x-x1)*f21+(x2-x)*f11))                   \
    / ((x2-x1)*(y2-y1)))

namespace math {

template<class T>
inline T interpolate(T x, T x1, T x2, T f1, T f2) {
  static_assert(std::is_floating_point<T>::value, 
    "T MUST be of floating-point type.");
  
  return LERP(x, x1, x2, f1, f2);
}

template<class F, class T>
inline T interpolate(T x, T x1, T x2, F f) {
  static_assert(std::is_floating_point<T>::value, 
    "T MUST be of floating-point type.");
  
  return interpolate(x, x1, x2, f(x1), f(x2));
}

template<class T>
inline T interpolate(T x, T y, T x1, T y1, T x2, T y2, 
    T f11, T f12, T f21, T f22) {
  static_assert(std::is_floating_point<T>::value, 
    "T MUST be of floating-point type.");

  return BLERP(x, y, x1, y1, x2, y2,
      f11, f12, f21, f22);
}

template<class F, class T>
inline T interpolate(T x, T y, T x1, T y1, T x2, T y2, F f) {
  static_assert(std::is_floating_point<T>::value, 
    "T MUST be of floating-point type.");

  return interpolate(x, y, x1, y1, x2, y2,
    f(x1, y1), f(x1, y2), f(x2, y1), f(x2, y2));
}

} // namespace math

#endif // VRISHE_INTERPOLATION_H_