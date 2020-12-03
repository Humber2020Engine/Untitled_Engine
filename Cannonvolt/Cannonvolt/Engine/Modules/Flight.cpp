#include "Flight.h"
#include "../../Game/Character.h"

Flight::Flight()
{
}

Flight::~Flight()
{
}

bool Flight::Initilize()
{
	Character::SetMod("Flight", true);
	Character::SetMod("Shoot", true);

	return true;
}
