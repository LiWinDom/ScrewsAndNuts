#include "RandomBot.h"

#include "../Game.h"

BotThink RandomBot::think(Game* game) const {
	uint16_t randomIndex = std::rand() % game->getPossibleMoves().size();
	return BotThink(std::pair<uint8_t, uint8_t>(game->getPossibleMoves()[randomIndex].first, game->getPossibleMoves()[randomIndex].second),
		std::pair<uint16_t, uint16_t>(0, 0));
}
