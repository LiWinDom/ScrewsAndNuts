#include "ImpossibleBot.h"

#include "../Game.h"

BotThink ImpossibleBot::think(Game* game) const {
	BotThink bestMove(std::pair<uint8_t, uint8_t>(0, 0), std::pair<uint16_t, uint16_t>(0, 32000));

	ImpossibleBot enemy(game->getWaitingPlayer()->getNumber());
	enemy.setThinkingLimit(_thinkingLimit - 1);

	for (uint16_t i = 0; i < game->getPossibleMoves().size(); ++i) {
		uint8_t x = game->getPossibleMoves()[i].first, y = game->getPossibleMoves()[i].second;
		game->move(x, y);

		BotThink curMove(std::pair<uint8_t, uint8_t>(x, y), std::pair<uint16_t, uint16_t>(countScore(game->getField(), game->getWinNumber()), enemy.countScore(game->getField(), game->getWinNumber())));
		if (enemy._thinkingLimit > 0 && game->getPossibleMoves().size() > 0) {
			// Enemy move
			curMove = enemy.think(game);
			curMove.addMove(x, y);
		}
		game->undo(1);

		if (curMove.getBestScore().first >= 32000) {
			bestMove = curMove;
			break;
		}
		if (curMove.getBestScore().second >= 32000) continue;

		if (curMove.getBestScore().first - curMove.getBestScore().second >= bestMove.getBestScore().first - bestMove.getBestScore().second) {
			if (curMove.getBestScore().first - curMove.getBestScore().second > bestMove.getBestScore().first - bestMove.getBestScore().second) {
				bestMove = curMove;
			}
			else if (curMove.getMoves().size() < bestMove.getMoves().size()) {
				bestMove = curMove;
			}
		}
	}

	return bestMove;
}
