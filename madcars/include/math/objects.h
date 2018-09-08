#pragma once

#ifndef VRISHE_MATH_OBJECTS_H_
#define VRISHE_MATH_OBJECTS_H_

#include <cstring>
#include <type_traits>

namespace math {

template<class TValue>
struct Grid {

  typedef typename std::remove_reference<TValue>::type value_type;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;

  template<size_t TRows, size_t TCols>
  Grid(const value_type (&values)[TRows][TCols])
      : cols(TCols), rows(TRows), size(TCols*TRows) {
    data_ = new value_type[size];
    std::memcpy(data_, &values[0][0], sizeof(values));
  }
  Grid(size_t rows, size_t cols)
      : cols(cols), rows(rows), size(rows*cols) {
    data_ = new value_type[size];
  }

  Grid(const Grid<TValue>&) =delete;
  Grid(Grid<TValue> &&src)
      : cols(src.cols), rows(src.rows), size(src.size) {
    data_ = nullptr;
    std::swap(data_, src.data_);
  }

  ~Grid() {
    delete[] data_;
  }

  Grid<TValue>& operator=(const Grid<TValue>&) =delete;
  Grid<TValue>& operator=(Grid<TValue>&& src)  =delete;

  const size_t cols;
  const size_t rows;
  const size_t size;

  value_type* c_ptr() { return data_; }

  typedef value_type *row_type;
  typedef const value_type *const_row_type;
  row_type operator[](size_t row) { return data_+row*cols; }
  const_row_type operator[](size_t row) const { return data_+row*cols; }

  iterator begin() { return data_; }
  iterator end() { return begin() + size; }

  const_iterator cbegin() const { return data_; }
  const_iterator cend() const { return begin() + size; }

  size_t height() const { return rows; }
  size_t width() const { return cols; }

  template<class F>
  void map(F func) {
    auto value = data_;
    for (size_t i=0; i<rows; ++i)
      for (size_t j=0; j<cols; ++j)
        *value++=func(i, j);
  }

private:
  value_type* data_;
};

template<class TScalar, size_t TRows, size_t TCols>
struct Mat_ {
  static_assert(std::is_arithmetic<TScalar>::value, 
    "TScalar MUST be of arithmetic type."); 

  typedef TScalar value_type;
  typedef TScalar* iterator;
  typedef const TScalar* const_iterator;

  static const size_t Cols = TCols;
  static const size_t Rows = TRows; 
  static const size_t Size = TCols*TRows;

  TScalar data[TRows][TCols];

  TScalar (&operator[](size_t i))[TCols] { return data[i]; }
  const TScalar (&operator[](size_t i) const)[TCols] { return data[i]; }

  iterator begin() { return &data[0][0]; }
  iterator end() { return begin() + Size; }

  const_iterator cbegin() const { return &data[0][0]; }
  const_iterator cend() const { return cbegin() + Size; }
};

namespace Mat {

template<class TMat>
TMat unity() {
  constexpr size_t rank = TMat::Cols < TMat::Rows
    ? TMat::Cols : TMat::Rows;

  auto result = TMat { 0 };
  for (size_t i=0; i<rank; ++i)
    result[i][i]=1;
  return result;
}
template<class TMat>
TMat zero() {
  return TMat { 0 };
}

} // namespace Mat

template<class TScalar, size_t TSize>
struct Vec_ {
  static_assert(std::is_arithmetic<TScalar>::value, 
    "TScalar MUST be of arithmetic type."); 

  typedef TScalar value_type;
  typedef TScalar* iterator;
  typedef const TScalar* const_iterator;

  static const size_t Size = TSize;

  TScalar data[TSize];

  TScalar& operator[](size_t i) { return data[i]; }
  TScalar operator[](size_t i) const { return data[i]; }

  iterator begin() { return &data[0]; }
  iterator end() { return begin() + Size; }

  const_iterator cbegin() const { return &data[0]; }
  const_iterator cend() const { return cbegin() + Size; }
};


template<class TObj>
inline TObj& operator*=(TObj& obj, typename TObj::value_type scalar) {
  auto from=obj.begin(), 
       to=obj.end();

  while (from != to)
    *from++*=scalar;
}
template<class TObj>
inline TObj operator*(const TObj& obj, typename TObj::value_type scalar) {
  auto result=obj; result*=scalar;
  return result;  
}
template<class TObj>
inline TObj operator*(typename TObj::value_type scalar, const TObj& obj) {
  return obj*scalar;
}


#define MATH_DEFINE_MATRIX(type, suffix, rows, cols) \
  typedef Mat_<type, rows, cols> Mat##rows##cols##suffix
#define MATH_DEFINE_VECTOR(type, suffix, size) \
  typedef Vec_<type, size> Vec##size##suffix

;} // namespace math

#endif // VRISHE_MATH_OBJECTS_H_