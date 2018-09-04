
#include <iostream>
#include <map>
#include <string>
#include "model.h"
#include "strategy.h"
#include "nlohmann/json.hpp"

using nlohmann::json;
typedef void (*msg_proc_)(const json&);

using namespace model;
Match match;
Tick  tick;

int main() {
	using namespace std;
	static map<string, msg_proc_> handler {
		{ "new_match", [](const json& j) -> void {
			from_json(j, match);
			strategy::on_new_match(match.proto_car, match.proto_map,
					match.enemy_lives, match.my_lives);
		}},
		{ "tick", [](const json& j) -> void {
			from_json(j, tick);
			strategy::on_tick(match.proto_car, match.proto_map,
				tick.enemy_car, tick.my_car, tick.deadline_position,
					match.enemy_lives, match.my_lives);
		}}
	};
	for(json j;;) {
		cin >> j; cin.ignore();
		handler.at(j.at("type").get<string>())(j.at("params"));
		j.clear();
	}
}