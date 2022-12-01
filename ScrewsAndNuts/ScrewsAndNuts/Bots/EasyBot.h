#pragma once
#include "../Bot.h"

class EasyBot final : public Bot
{
public:
	EasyBot(const uint8_t& number) : Bot(number, "Easy bot", 2) {}

	~EasyBot() {};


	BotThink think(Game*) const override;
};

