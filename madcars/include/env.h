#ifndef VRISHE_ENV_
#define VRISHE_ENV_

#ifndef ENV_LOCAL
#include "../nlohmann/json.hpp"
#else // if defined(ENV_LOCAL)
#include "nlohmann/json.hpp"
#endif // ENV_LOCAL

#endif