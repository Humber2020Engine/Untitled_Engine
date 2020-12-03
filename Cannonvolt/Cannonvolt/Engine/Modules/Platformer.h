#pragma once

#include "Modular_Base.h"

class Platformer : public Modular_Base {
public: 
	Platformer();
	virtual ~Platformer();

	virtual bool Initilize() override;

};
