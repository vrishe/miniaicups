#pragma once

#ifndef VRISHE_PLANAR_RESTRICTED_H_
#define VRISHE_PLANAR_RESTRICTED_H_

#include "internal_.h"
#include "interpolation.h"
#include "objects.h"

namespace math {

// MATRIX 2x3
MATH_DEFINE_MATRIX(double, d, 2, 3);
MATH_DEFINE_MATRIX(float, f, 2, 3);

template<>
inline Mat23f& operator*=<Mat23f>(Mat23f& obj, float scalar) {
  obj[0][0]*=scalar; obj[0][1]*=scalar; obj[0][2]*=scalar;
  obj[1][0]*=scalar; obj[1][1]*=scalar; obj[1][2]*=scalar;
  return obj;
}

namespace Mat {

inline float det(const Mat23f& mat) {
  return mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];
}
inline Mat23f inv(const Mat23f& mat) {
  auto detInv = 1.f / det(mat);

  return Mat23f {
    // Row #1
     mat[1][1]*detInv, 
    -mat[0][1]*detInv,
     (mat[0][1]*mat[1][2]-mat[1][1]*mat[0][2])*detInv,
    // Row #2
    -mat[1][0]*detInv,
     mat[0][0]*detInv,
    -(mat[0][0]*mat[1][2]-mat[1][0]*mat[0][2])*detInv,
  };
}


inline Mat23f rotation(float r) {
  auto s = std::sin(r),
       c = std::cos(r);

  return Mat23f {
    c, -s,  0,
    s,  c,  0
  };
}
inline Mat23f rotation(float r, float cx, float cy) {
  auto s = std::sin(r),
       c = std::cos(r);

  return Mat23f {
    c, -s,  cx + s*cy - c*cx,
    s,  c,  cy - s*cx - c*cy,
  };
}

inline Mat23f scale(float sx, float sy) {
  return Mat23f { 
    sx, 0,  0, 
    0,  sy, 0,
  };
}
inline Mat23f scale(float s) {
  return scale(s, s);
}
inline Mat23f scale(float sx, float sy, float cx, float cy) {
  return Mat23f {
    sx, 0,  cx - sx*cx,
    0,  sy, cy - sy*cy,
  };
}
inline Mat23f scale(float s, float cx, float cy) {
  return scale(s, s, cx, cy);
}

inline Mat23f translation(float tx, float ty) {
  return Mat23f { 
    1, 0, tx, 
    0, 1, ty,
  };  
}

template<>
inline Mat23f unity<Mat23f>() {
  return Mat23f { 1, 0, 0, 0, 1, 0 };
}

} // namespace Mat

// VECTOR 2
MATH_DEFINE_VECTOR(double, d, 2);
MATH_DEFINE_VECTOR(float, f, 2);

template<>
inline Vec2f& operator*=<Vec2f>(Vec2f& obj, float scalar) {
  obj[0]*=scalar; obj[1]*=scalar;
  return obj;
}

namespace Vec {

inline float len(const Vec2f& vec) {
  return std::sqrt(vec[0]*vec[0]+vec[1]*vec[1]);
}

} // namespace Vec


inline Mat23f operator*(const Mat23f& a, const Mat23f& b) {
  return Mat23f {
    // Row #1
    a[0][0]*b[0][0]+a[0][1]*b[1][0],
    a[0][0]*b[0][1]+a[0][1]*b[1][1],
    a[0][0]*b[0][2]+a[0][1]*b[1][2]+a[0][2],
    // Row #2
    a[1][0]*b[0][0]+a[1][1]*b[1][0],
    a[1][0]*b[0][1]+a[1][1]*b[1][1],
    a[1][0]*b[0][2]+a[1][1]*b[1][2]+a[1][2],
  };
}
inline Vec2f operator*(const Mat23f& m, const Vec2f& v) {
  return Vec2f {
    m[0][0]*v[0]+m[0][1]*v[1]+m[0][2],
    m[1][0]*v[0]+m[1][1]*v[1]+m[1][2],
  };
}
inline Vec2f operator*(const Vec2f &v, const Mat23f& m) {
  return Vec2f {
    v[0]*m[0][0]+v[1]*m[1][0]+m[2][0],
    v[0]*m[0][1]+v[1]*m[1][1]+m[2][1],
  };
}

inline Mat23f& operator*=(Mat23f& a, const Mat23f& b) {
  return a = a*b;
}
inline Vec2f& operator*=(Vec2f& a, const Mat23f& b) {
  return a = a*b;
}


namespace PF {

template<class TValue, class TFunc>
Mat23f find(Grid<TValue>& grid, TFunc f, const Mat23f& transform = Mat::unity<Mat23f>()) {
  auto t = transform * Mat::translation(-.5f*(grid.width() - 1), -.5f*(grid.height() - 1));

  Vec2f pt;
  for (size_t i = 0; i < grid.rows; ++i) {
    pt[1]=i;
    for (size_t j = 0; j < grid.cols; ++j) {
      pt[0]=j;

      grid[i][j]=f(t*pt);
    }
  }
  return Mat::inv(t);
}

template<class TValue>
float get(const Grid<TValue>& grid, const Mat23f transform, const Vec2f& location) {
  auto l = transform*location;

  using namespace std;
  auto x1 = min(size_t(fmax(floor(l[0]), 0.f)), grid.width()),
       x2 = min(size_t(fmax(ceil(l[0]), 0.f)), grid.width()),
       y1 = min(size_t(fmax(floor(l[1]), 0.f)), grid.height()),
       y2 = min(size_t(fmax(ceil(l[1]), 0.f)), grid.height());

  auto f11 = grid[x1][y1], 
       f22 = grid[x2][y2];

  if (x1 != x2 && y1 != y2) {
    auto f12 = grid[x1][y2], 
         f21 = grid[x2][y1];

    return interpolate<float>(l[0], l[1],
      x1, y1, x2, y2, f11, f12, f21, f22);    
  }
  if (x1 != x2)
    return interpolate<float>(l[0], x1, x2, f11, f22);
  if (y1 != y2)
    return interpolate<float>(l[1], y1, y2, f11, f22);

  return f11;
}

} // namespace pf
} // namespace math

#endif // VRISHE_PLANAR_RESTRICTED_H_