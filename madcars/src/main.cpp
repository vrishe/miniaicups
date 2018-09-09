
#include <iostream>
#include <map>
#include <string>

#include "env.h"
#include "model.h"
#include "strategy.h"

using nlohmann::json;
typedef void (*msg_proc_)(const json&);

using namespace model;
Match match;
Tick  tick;

static size_t ticks_ = 0,
	ticks_total_ = 0;

int main() {
	using namespace std;
	static map<string, msg_proc_> handler {
		{ "new_match", [](const json& j) -> void {
			from_json(j, match);
			strategy::on_new_match(match.proto_car, match.proto_map,
					match.enemy_lives, match.my_lives);
			ticks_ = 0;
			ticks_total_++;
		}},
		{ "tick", [](const json& j) -> void {
			from_json(j, tick);
			strategy::on_tick(match.proto_car, match.proto_map,
				tick.enemy_car, tick.my_car, tick.deadline_position,
					match.enemy_lives, match.my_lives);
			ticks_++;
			ticks_total_++;
		}}
	};
	for(json j;;) {
		cin >> j; cin.ignore();
		handler.at(j.at("type").get<string>())(j.at("params"));
		j.clear();
	}
}

namespace env {
size_t get_ticks()       { return ticks_; }
size_t get_ticks_total() { return ticks_total_; }
} // namespace env
