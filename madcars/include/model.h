#ifndef VRISHE_MODEL_H_
#define VRISHE_MODEL_H_

#include <cstdint>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

namespace model {

	using nlohmann::json;

	struct Point2D {
		double x,y;

		friend void from_json(const json& src, Point2D& dst) {
			dst.x = src.at(0);
			dst.y = src.at(1);
		}
	}; // struct Point2D

	struct Transform2D: public Point2D {
		double angle;

		friend void from_json(const json& src, Transform2D& dst) {
			dst.x = src.at(0);
			dst.y = src.at(1);
			dst.angle = src.at(2);
		}
	}; // struct Transform2D


	struct Car {
#define WHEEL_REAR  0
#define WHEEL_FRONT 1

		Transform2D wheels[2];
		Point2D position;
		double  rotation;
		float   side;

		friend void from_json(const json& src, Car& dst) {
			dst.wheels[WHEEL_FRONT] = src.at(4);
			dst.wheels[WHEEL_REAR]  = src.at(3);
			dst.position = src.at(0);
			dst.rotation = src.at(1);
			dst.side = src.at(2);
		}
	}; // struct Car

	struct ProtoCar {
		std::vector<Point2D> button_poly,
			car_body_poly;

		Point2D front_wheel_damp_position,
			front_wheel_joint,
			front_wheel_position;
		Point2D rear_wheel_damp_position,
			rear_wheel_joint,
			rear_wheel_position;

		double car_body_mass,
			car_body_elasticity,
			car_body_friction,
			drive,
			max_angular_speed,
			max_speed;

		double front_wheel_radius,
			front_wheel_mass,
			front_wheel_friction,
			front_wheel_elasticity,
			front_wheel_damp_damping,
			front_wheel_damp_length,
			front_wheel_damp_stiffness;
		double rear_wheel_radius,
			rear_wheel_mass,
			rear_wheel_friction,
			rear_wheel_elasticity,
			rear_wheel_damp_damping,
			rear_wheel_damp_length,
			rear_wheel_damp_stiffness;

		int32_t external_id;

		bool squared_wheels;

		friend void from_json(const json& src, ProtoCar& dst) {
			dst.button_poly = src.at("button_poly").get<std::vector<Point2D>>();
			dst.car_body_poly = src.at("car_body_poly").get<std::vector<Point2D>>();
			dst.front_wheel_damp_position = src.at("front_wheel_damp_position").get<Point2D>();
			dst.front_wheel_joint = src.at("front_wheel_joint").get<Point2D>();
			dst.front_wheel_position = src.at("front_wheel_position").get<Point2D>();
			dst.rear_wheel_damp_position = src.at("rear_wheel_damp_position").get<Point2D>();
			dst.rear_wheel_joint = src.at("rear_wheel_joint").get<Point2D>();
			dst.rear_wheel_position = src.at("rear_wheel_position").get<Point2D>();
			dst.car_body_mass = src.at("car_body_mass").get<double>();
			dst.car_body_elasticity = src.at("car_body_elasticity").get<double>();
			dst.car_body_friction = src.at("car_body_friction").get<double>();
			dst.drive = src.at("drive").get<double>();
			dst.max_angular_speed = src.at("max_angular_speed").get<double>();
			dst.max_speed = src.at("max_speed").get<double>();
			dst.front_wheel_radius = src.at("front_wheel_radius").get<double>();
			dst.front_wheel_mass = src.at("front_wheel_mass").get<double>();
			dst.front_wheel_friction = src.at("front_wheel_friction").get<double>();
			dst.front_wheel_elasticity = src.at("front_wheel_elasticity").get<double>();
			dst.front_wheel_damp_damping = src.at("front_wheel_damp_damping").get<double>();
			dst.front_wheel_damp_length = src.at("front_wheel_damp_length").get<double>();
			dst.front_wheel_damp_stiffness = src.at("front_wheel_damp_stiffness").get<double>();
			dst.rear_wheel_radius = src.at("rear_wheel_radius").get<double>();
			dst.rear_wheel_mass = src.at("rear_wheel_mass").get<double>();
			dst.rear_wheel_friction = src.at("rear_wheel_friction").get<double>();
			dst.rear_wheel_elasticity = src.at("rear_wheel_elasticity").get<double>();
			dst.rear_wheel_damp_damping = src.at("rear_wheel_damp_damping").get<double>();
			dst.rear_wheel_damp_length = src.at("rear_wheel_damp_length").get<double>();
			dst.rear_wheel_damp_stiffness = src.at("rear_wheel_damp_stiffness").get<double>();
			dst.external_id = src.at("external_id").get<int32_t>();
			// Optional
			auto squared_wheels_opt = src.find("squared_wheels");
			dst.squared_wheels = squared_wheels_opt != src.end()
				&& squared_wheels_opt->get<bool>();
		}
	}; // struct ProtoCar

	struct Segment {
		Point2D start,
			end;
		double thickness;

		friend void from_json(const json& src, Segment& dst) {
			dst.start = src.at(0);
			dst.end = src.at(1);
			dst.thickness = src.at(2);
		}
	}; // struct Segment

	struct ProtoMap {
		std::vector<Segment> segments;
		int32_t external_id;

		friend void from_json(const json& src, ProtoMap& dst) {
			dst.segments = src.at("segments").get<std::vector<Segment>>();
			dst.external_id = src.at("external_id").get<int>();
		}
	}; // struct ProtoMap

	struct Match {
		ProtoCar proto_car;

		int32_t enemy_lives,
			my_lives;

		ProtoMap proto_map;

		friend void from_json(const json& src, Match& dst) {
			dst.proto_car = src.at("proto_car").get<ProtoCar>();
			dst.proto_map = src.at("proto_map").get<ProtoMap>();
			dst.enemy_lives = src.at("enemy_lives").get<int32_t>();
			dst.my_lives = src.at("my_lives").get<int32_t>();
		}
	}; // struct Match

	struct Tick {
		Car enemy_car,
			my_car;
		
		double deadline_position;

		friend void from_json(const json& src, Tick& dst) {
			dst.enemy_car = src.at("enemy_car").get<Car>();
			dst.my_car = src.at("my_car").get<Car>();
			dst.deadline_position = src.at("deadline_position").get<double>();
		}
	}; // struct Tick

} // namespace model

#endif //VRISHE_MODEL_H_