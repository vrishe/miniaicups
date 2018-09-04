#include "strategy.h"

#include <iostream>

namespace strategy {

size_t ticks_count = 0;

void on_new_match(const ProtoCar& proto_car, const ProtoMap& proto_map,
		int32_t enemy_lives, int32_t my_lives) {

	ticks_count = 0;
	std::cerr << "NEW MATCH!!" << std::endl
		<< "drive: " << proto_car.drive << std::endl
		<< "map id:" << proto_map.external_id << std::endl
		<< "map segments count: " << proto_map.segments.size() << std::endl;
}
void on_tick(const ProtoCar& proto_car, const ProtoMap& proto_map,
		const Car& enemy_car, const Car& my_car, 
		double deadline_position,
		int32_t enemy_lives, int32_t my_lives) {

	std::cerr << "TICK #" << (ticks_count + 1) << std::endl
		<< "drive: " << proto_car.drive << std::endl
		<< "map id:" << proto_map.external_id << std::endl
		<< "map segments count: " << proto_map.segments.size() << std::endl
		<< "my car position: " << my_car.position.x << "; " << my_car.position.y << std::endl
		<< "deadline position: " << deadline_position << std::endl;

	std::cout << "{ \"command\": \"left\" }" << std::endl;
	++ticks_count;
}

} // namespace strategy