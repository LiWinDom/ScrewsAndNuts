#pragma once
#include "../Bot.h"

class ImpossibleBot final : public Bot
{
public:
	ImpossibleBot(const uint8_t& number) : Bot(number, "テスト", 3) {}

	~ImpossibleBot() {};


	BotThink think(Game*) const override;
};

