#include "Human.h"

bool Human::isBot() const {
	return false;
}

void Human::think(Game* game) const {
	throw std::exception("Human can't think");
	return;
}
