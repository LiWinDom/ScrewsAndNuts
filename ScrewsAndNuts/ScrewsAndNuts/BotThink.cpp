#include "BotThink.h"

void BotThink::addMove(const uint8_t& x, const uint8_t& y) {
	_moves.insert(_moves.begin(), {x, y});
	std::swap(_bestScore.first, _bestScore.second);
	return;
}