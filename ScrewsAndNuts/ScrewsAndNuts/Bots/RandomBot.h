#pragma once
#include "../Bot.h"

class RandomBot final : public Bot
{
public:
	RandomBot(const uint8_t& number) : Bot(number, "Garbage Collector", 1) {}

	~RandomBot() {};


	BotThink think(Game*) const override;
};

