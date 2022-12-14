#pragma once
#include <algorithm>
#include <vector>

#include "Bot.h"
#include "BotThink.h"
#include "IPlayer.h"

class Game final
{
public:
	Game(const uint8_t& fieldWidth, const uint8_t& fieldHeight, IPlayer* player1, IPlayer* player2, const uint8_t& firstPlayer = 0) :
	_width(fieldWidth), _height(fieldHeight), _player1(player1), _player2(player2), _field(_width * _height + 1, std::vector<std::vector<uint8_t>>(_width, std::vector<uint8_t>(_height, 0))) {
		if (firstPlayer == 0) {
			if (std::rand() % 2) {
				_curPlayer = _player1;
			}
			else {
				_curPlayer = _player2;
			}
		}
		else if (firstPlayer == _player1->getNumber()) {
			_curPlayer = _player1;
		}
		else if (firstPlayer == _player2->getNumber()) {
			_curPlayer = _player2;
		}
		else {
			throw std::exception("Incorrect first player");
		}
		return;
	}

	~Game() {
		delete _player1;
		delete _player2;
		return;
	}

	IPlayer* getCurPlayer() const {
		return _curPlayer;
	}

	IPlayer* getWaitingPlayer() const {
		if (_curPlayer == _player1) {
			return _player2;
		}
		return _player1;
	}

	uint8_t getCurMove() const {
		return _curMove;
	}

	IPlayer* getWinner() const {
		return _winner;
	}

	std::vector<std::vector<uint8_t>> getField() const {
		return _field[_curMove];
	}

	std::vector<std::pair<uint8_t, uint8_t>> getWinCombination() const {
		return _winCombination;
	}

	uint8_t getWinNumber() {
		return _winNumber;
	}


	bool checkMove(const uint8_t&, const uint8_t&) const;

	std::vector<std::pair<uint8_t, uint8_t>> getPossibleMoves() const;

	bool move(const uint8_t& x, const uint8_t& y);

	void undo(const uint8_t&);

	void think(const int8_t& = -1, const int8_t& = -1);

private:
	const uint8_t _width, _height;

	IPlayer* _player1, *_player2;
	IPlayer* _curPlayer, *_winner = nullptr;
	uint8_t _curMove = 0;

	std::vector<std::vector<std::vector<uint8_t>>> _field;
	std::vector<std::pair<uint8_t, uint8_t>> _winCombination;
	static constexpr uint8_t _winNumber = 5;

	bool winCheck(const uint8_t&, const uint8_t&);
};
