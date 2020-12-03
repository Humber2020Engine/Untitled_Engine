#pragma once
#include "Modular_Base.h"

class Flight : public Modular_Base {
public:
	Flight();
	virtual ~Flight();

	virtual bool Initilize() override;

};