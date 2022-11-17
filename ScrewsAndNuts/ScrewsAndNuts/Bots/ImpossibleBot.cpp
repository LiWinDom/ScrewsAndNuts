#include "ImpossibleBot.h"

#include "../Game.h"

BotThink ImpossibleBot::think(Game* game) const {
	ImpossibleBot enemy(game->getWaitingPlayer()->getNumber());
	enemy.setThinkingLimit(_thinkingLimit - 1);

	BotThink bestMove(std::pair<uint8_t, uint8_t>(game->getPossibleMoves()[0].first, game->getPossibleMoves()[0].second),
		std::pair<uint16_t, uint16_t>(0, 32000));

	std::vector<std::pair<uint8_t, uint8_t>> movesNum = game->getPossibleMoves();

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

		if (curMove.getBestScore().first >= 16000 && curMove.getBestScore().second < 32000) {
			bestMove = curMove;
			if (curMove.getMoves().size() < 2) {
				break;
			}
			continue;
		}
		if (curMove.getBestScore().second >= 16000) {
			continue;
		}

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
