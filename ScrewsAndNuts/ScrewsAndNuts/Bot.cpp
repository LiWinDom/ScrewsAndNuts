#include "Bot.h"

bool Bot::isBot() const {
	return true;
}


uint16_t Bot::countScore(const std::vector<std::vector<uint8_t>>& field, const uint8_t& winNumber) const {
	uint16_t total = 0;
	uint16_t opened4 = 0;
	uint16_t closed4 = 0;
	uint16_t opened3 = 0;

	for (uint8_t x = 0; x < field.size(); ++x) {
		for (uint8_t y = 0; y < field[x].size(); ++y) {
			if (field[x][y] == 0) continue;

			// Horizontal count
			uint8_t counter = 0;
			uint8_t opened = 0;
			// Left
			for (int8_t i = x; i >= 0; --i) {
				if (field[i][y] == 0) {
					++opened;
					break;
				}
				else if (field[i][y] != getNumber()) {
					break;
				}
				++counter;
			}
			// Right
			for (int8_t i = x + 1; i < field.size(); ++i) {
				if (field[i][y] == 0) {
					++opened;
					break;
				}
				else if (field[i][y] != getNumber()) {
					break;
				}
				++counter;
			}
			// Counting
			if (counter >= winNumber) {
				return 32000;
			}
			if (opened == 2) {
				if (counter >= winNumber - 1) {
					++opened4;
				}
				else if (counter >= winNumber - 2) {
					++opened3;
				}
				total += std::pow(counter, counter);
			}
			else if (opened == 1) {
				if (counter >= winNumber - 1) {
					++closed4;
				}
				else {
					total += counter;
				}
			}

			// Vertical check
			counter = 0;
			opened = 0;
			// Up
			for (int8_t i = y; i >= 0; --i) {
				if (field[x][i] == 0) {
					++opened;
					break;
				}
				else if (field[x][i] != getNumber()) {
					break;
				}
				++counter;
			}
			// Down
			for (int8_t i = y + 1; i < field[x].size(); ++i) {
				if (field[x][i] == 0) {
					++opened;
					break;
				}
				else if (field[x][i] != getNumber()) {
					break;
				}
				++counter;
			}
			// Counting
			if (counter >= winNumber) {
				return 32000;
			}
			if (opened == 2) {
				if (counter >= winNumber - 1) {
					++opened4;
				}
				else if (counter >= winNumber - 2) {
					++opened3;
				}
				total += std::pow(counter, counter);
			}
			else if (opened == 1) {
				if (counter >= winNumber - 1) {
					++closed4;
				}
				else {
					total += counter;
				}
			}

			// Left diagonal check
			counter = 0;
			opened = 0;
			// Up
			for (int8_t i = 0; x - i >= 0 && y - i >= 0; ++i) {
				if (field[x - i][y - i] == 0) {
					++opened;
					break;
				}
				else if (field[x - i][y - i] != getNumber()) {
					break;
				}
				++counter;
			}
			// Down
			for (int8_t i = 1; x + i < field.size() && y + i < field[x].size(); ++i) {
				if (field[x + i][y + i] == 0) {
					++opened;
					break;
				}
				else if (field[x + i][y + i] != getNumber()) {
					break;
				}
				++counter;
			}
			// Counting
			if (counter >= winNumber) {
				return 32000;
			}
			if (opened == 2) {
				if (counter >= winNumber - 1) {
					++opened4;
				}
				else if (counter >= winNumber - 2) {
					++opened3;
				}
				total += std::pow(counter, counter);
			}
			else if (opened == 1) {
				if (counter >= winNumber - 1) {
					++closed4;
				}
				else {
					total += counter;
				}
			}

			// Right diagonal check
			counter = 0;
			opened = 0;
			// Up
			for (int8_t i = 0; x - i >= 0 && y + i < field[x].size(); ++i) {
				if (field[x - i][y + i] == 0) {
					++opened;
					break;
				}
				else if (field[x - i][y + i] != getNumber()) {
					break;
				}
				++counter;
			}
			// Down
			for (int8_t i = 1; x + i < field.size() && y - i >= 0; ++i) {
				if (field[x + i][y - i] == 0) {
					++opened;
					break;
				}
				else if (field[x + i][y - i] != getNumber()) {
					break;
				}
				++counter;
			}
			// Counting
			if (counter >= winNumber) {
				return 32000;
			}
			if (opened == 2) {
				if (counter >= winNumber - 1) {
					++opened4;
				}
				else if (counter >= winNumber - 2) {
					++opened3;
				}
				total += std::pow(counter, counter);
			}
			else if (opened == 1) {
				if (counter >= winNumber - 1) {
					++closed4;
				}
				else {
					total += counter;
				}
			}
		}
	}

	if (opened4 / 4 > 0 || (closed4 / 4 + opened3 / 2) > 1) total = std::max((uint16_t)16000, total);
	else if (closed4 / 4 > 0 || opened3 / 3 > 0) total = std::max((uint16_t)8000, total);
	return total;
}
