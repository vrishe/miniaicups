#ifndef VRISHE_STRATEGY_
#define VRISHE_STRATEGY_

#include "model.h"

namespace strategy {

using namespace model;

extern size_t ticks_count;

void on_new_match(const ProtoCar&, const ProtoMap&,
		int32_t enemy_lives, int32_t my_lives);
void on_tick(const ProtoCar&, const ProtoMap&,
	const Car& enemy_car, const Car& my_car,
	double deadline_position,
	int32_t enemy_lives, int32_t my_lives);

} // namespace strategy
#endif