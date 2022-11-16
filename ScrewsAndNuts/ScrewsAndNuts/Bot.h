#pragma once
#include <cmath>
#include <vector>

#include "BotThink.h"
#include "IPlayer.h"

class Game;

class Bot abstract : public IPlayer
{
public:
	Bot(const uint8_t& number, const std::string& name, const uint8_t& thinkingLimit) :
		IPlayer(number, name), _thinkingLimit(thinkingLimit) {};

	~Bot() {};


	bool isBot() const override final;

	virtual BotThink think(Game*) const = 0;

protected:
	uint8_t _thinkingLimit;

	void setThinkingLimit(const uint8_t& limit) {
		_thinkingLimit = limit;
		return;
	}

	uint16_t countScore(const std::vector<std::vector<uint8_t>>&, const uint8_t& = 5) const;
};

