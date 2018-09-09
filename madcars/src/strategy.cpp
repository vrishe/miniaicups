#include "strategy.h"

#include <array>
#include <iostream>
#include <string>

#include "env.h"
#include "math/linalg.h"

namespace strategy {

namespace {

// Point buffer, that holds points for both body and button polygons
// per playing side. 0th buffer is for enemy, the last one is for us.  
// 

math::Mat23f mtx;
std::vector<math::Vec2f> point_buffer[2];

void prepare_point_buffer(const ProtoCar& proto_car) {
	auto buffer_size = proto_car.button_poly.size()
		+ proto_car.car_body_poly.size();

	point_buffer[0].resize(buffer_size);
	point_buffer[1].resize(buffer_size);
}

inline void transform_point_buffer_(const ProtoCar& proto_car,
		const Car& car, size_t buffer_idx) {

	using namespace math::Mat;

	auto mtx = translation(car.position[0], car.position[1])
		* rotation(car.rotation)
		* scaling(car.side, 1);

	auto p_iter = point_buffer[buffer_idx].begin();
	for (const auto& p: proto_car.car_body_poly)
		*p_iter++ = p*mtx;
	for (const auto& p: proto_car.button_poly)
		*p_iter++ = p*mtx;	
}

void transform_point_buffer(const ProtoCar& proto_car,
		const Car& enemy_car, const Car& my_car) {

	transform_point_buffer_(proto_car, enemy_car, 0);
	transform_point_buffer_(proto_car, my_car,    1);
}

} // namespace

void on_new_match(const ProtoCar& proto_car, const ProtoMap& proto_map,
		int32_t enemy_lives, int32_t my_lives) {

	prepare_point_buffer(proto_car);
}
void on_tick(const ProtoCar& proto_car, const ProtoMap& proto_map,
		const Car& enemy_car, const Car& my_car, 
		double deadline_position,
		int32_t enemy_lives, int32_t my_lives) {

	transform_point_buffer(proto_car, enemy_car, my_car);
	std::cout << "{\"command\": \"stop\"}" << std::endl;
}

} // namespace strategy