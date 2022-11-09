#include "Game.h"

bool Game::checkMove(const uint8_t& x, const uint8_t& y) {
	if (_field[_curMove][x][y] != 0 || _winner != nullptr) return false;
	return true;
}

std::vector<std::pair<uint8_t, uint8_t>> Game::possibleMoves() {
	std::vector<std::pair<uint8_t, uint8_t>> possibilities;

	for (uint8_t i = 0; i < 8; ++i) {
		for (uint8_t j = 0; j < 8; ++j) {
			if (checkMove(i, j)) {
				possibilities.push_back(std::pair<uint8_t, uint8_t>(i, j));
			}
		}
	}
	return possibilities;
}

bool Game::move(const uint8_t& x, const uint8_t& y) {
	if (!checkMove(x, y) || _winner != nullptr) return false;

	_field[_curMove + 1] = _field[_curMove];
	++_curMove;
	_field[_curMove][x][y] = _curPlayer->getNumber();
	if (winCheck(x, y)) {
		return true;
	}

	if (_curPlayer == _player1) {
		_curPlayer = _player2;
	}
	else {
		_curPlayer = _player1;
	}
	return true;
}

void Game::undo(const uint8_t& movesNum) {
	_curMove -= std::min(_curMove, movesNum);
	_winner = nullptr;
	_winCombination = std::vector<std::pair<uint8_t, uint8_t>>(0, std::pair<uint8_t, uint8_t>(0, 0));
	return;
}

void Game::think(const int8_t& mouseClickX, const int8_t& mouseClickY) {
	if (_winner != nullptr) return;

	if (_curPlayer->isBot()) {
		_curPlayer->think(this);
	}
	else {
		if (mouseClickX > -1 && mouseClickX < _width && mouseClickY > -1 && mouseClickY < _height) {
			move(mouseClickX, mouseClickY);
		}
	}
	return;
}


bool Game::winCheck(const uint8_t& x, const uint8_t& y) {
	// Horizontal check
	uint8_t counter = 0;
	// Left
	for (int8_t i = x; i >= 0; --i) {
		if (_field[_curMove][i][y] != _curPlayer->getNumber()) {
			break;
		}
		_winCombination.push_back(std::pair<uint8_t, uint8_t>(i, y));
		++counter;
	}
	// Right
	for (int8_t i = x + 1; i < _width; ++i) {
		if (_field[_curMove][i][y] != _curPlayer->getNumber()) {
			break;
		}
		_winCombination.push_back(std::pair<uint8_t, uint8_t>(i, y));
		++counter;
	}
	// Check
	if (counter >= _winNumber) {
		_winner = _curPlayer;
		return true;
	}
	_winCombination = std::vector<std::pair<uint8_t, uint8_t>>(0, std::pair<uint8_t, uint8_t>(0, 0));

	// Vertical check
	counter = 0;
	// Up
	for (int8_t i = y; i >= 0; --i) {
		if (_field[_curMove][x][i] != _curPlayer->getNumber()) {
			break;
		}
		_winCombination.push_back(std::pair<uint8_t, uint8_t>(x, i));
		++counter;
	}
	// Down
	for (int8_t i = y + 1; i < _height; ++i) {
		if (_field[_curMove][x][i] != _curPlayer->getNumber()) {
			break;
		}
		_winCombination.push_back(std::pair<uint8_t, uint8_t>(x, i));
		++counter;
	}
	// Check
	if (counter >= _winNumber) {
		_winner = _curPlayer;
		return true;
	}
	_winCombination = std::vector<std::pair<uint8_t, uint8_t>>(0, std::pair<uint8_t, uint8_t>(0, 0));

	return false;
}
