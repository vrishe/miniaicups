#include "strategy.h"

#include <iostream>
#include <string>

namespace strategy {

size_t ticks_count = 0;

void on_new_match(const ProtoCar& proto_car, const ProtoMap& proto_map,
		int32_t enemy_lives, int32_t my_lives) {

	ticks_count = 0;
}
void on_tick(const ProtoCar& proto_car, const ProtoMap& proto_map,
		const Car& enemy_car, const Car& my_car, 
		double deadline_position,
		int32_t enemy_lives, int32_t my_lives) {

	std::cerr << "car side: " << my_car.side << ", " << enemy_car.side << std::endl;
	std::cout << "{ \"command\": \"stop\" }" << std::endl;
	++ticks_count;
}

} // namespace strategy