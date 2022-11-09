#pragma once
#include <vector>

#include "IPlayer.h"

class Bot abstract : public IPlayer
{
public:
	Bot(const uint8_t& number, const std::string& name) : IPlayer(number, name) {};

	~Bot() {};


	bool isBot() const override;

	void think(Game*) const override = 0;

protected:
	uint16_t scoreCount(const std::vector<std::vector<uint8_t>>&);
};

