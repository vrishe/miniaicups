#pragma once

#ifndef VRISHE_MATH_INTERNAL_H_
#define VRISHE_MATH_INTERNAL_H_

#define PI      3.14159265358979323846   // pi
#define PHI     1.6180339887498948482045868343656 // Golden Ratio
#define PHI_INV 0.6180339887498948482045868343656 // 1 / Golden Ratio

#include <cmath>
#include <cstdint>

#define RAD(degrees) ((PI*degrees)/180.)
#define DEG(radians) ((180.*radians)/PI)

#endif // VRISHE_MATH_INTERNAL_H_