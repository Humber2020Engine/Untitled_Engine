#ifndef MODULAR_BASE_H
#define MODULAR_BASE_H


class Modular_Base{

public:	
	Modular_Base();
	virtual ~Modular_Base();

	virtual bool Initilize() = 0;

};

#endif // !MODULAR_BASE_H