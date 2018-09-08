#pragma once

#ifndef VRISHE_ENV_H_
#define VRISHE_ENV_H_

#ifndef ENV_LOCAL
#include "../nlohmann/json.hpp"
#else // if defined(ENV_LOCAL)
#include "nlohmann/json.hpp"
#endif // ENV_LOCAL

#endif // VRISHE_ENV_H_
