#include "Bot.h"

bool Bot::isBot() const {
	return true;
}


uint16_t Bot::scoreCount(const std::vector<std::vector<uint8_t>>& field) {
	uint16_t total = 0;
	for (uint8_t i = 0; i < field.size(); ++i) {
		for (uint8_t j = 0; j < field[i].size(); ++j) {

		}
	}
	return total;
}
