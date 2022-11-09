#pragma once
#include <string>

class Game;

class IPlayer abstract
{
public:
	IPlayer(const uint8_t& number, const std::string& name = "") :
		_number(number), _name(name) {
		if (_number == 0) {
			throw std::exception("Player number cannot be 0");
		}
		return;
	};

	virtual ~IPlayer() {};

	virtual uint8_t getNumber() const final {
		return _number;
	}

	virtual std::string getName() const final {
		return _name;
	}

	
	virtual bool isBot() const = 0;

	virtual void think(Game*) const = 0;

private:
	const uint8_t _number;
	const std::string _name;
};

