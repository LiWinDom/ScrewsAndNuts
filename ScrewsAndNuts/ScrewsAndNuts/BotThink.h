#pragma once
#include <algorithm>
#include <vector>

class BotThink final
{
public:
	BotThink(const std::pair<uint8_t, uint8_t>& move, const std::pair<uint16_t, uint16_t>& score) :
		_moves({move}), _bestScore(score) {};

	~BotThink() {}

	std::vector<std::pair<uint8_t, uint8_t>> getMoves() const {
		return _moves;
	}

	std::pair<uint16_t, uint16_t> getBestScore() const {
		return _bestScore;
	}


	void addMove(const uint8_t&, const uint8_t&);

private:
	std::vector<std::pair<uint8_t, uint8_t>> _moves;
	std::pair<uint16_t, uint16_t> _bestScore;
};

