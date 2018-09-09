#ifndef VRISHE_UTILITY_H_
#define VRISHE_UTILITY_H_

extern "C++" {
  template <typename Ty, size_t arraySize>
  char(*my_countof_helper(const Ty(&arr)[arraySize]))[arraySize];
}

#define countof_(arr) (sizeof(*my_countof_helper(arr)) + 0)

namespace num {

template <class Number>
inline Number signum(Number value) {
    static_assert(std::is_signed<Number>::value,
  		"A signed number value is only supported.");

    return (Number(0) < value) - (value < Number(0));
}

} // namespace num

#endif //VRISHE_UTILITY_H_