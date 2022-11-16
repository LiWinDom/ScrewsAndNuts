#pragma once
#include <algorithm>

#include "IPlayer.h"

class Human final : public IPlayer
{
public:
	Human(const uint8_t& number, const std::string& name = "") : IPlayer(number, name) {}

	~Human() {};


	virtual bool isBot() const override;
};

