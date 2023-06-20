#pragma once
#include "Multimetr.h"

class Voltmeter: public Multimetr
{
	
public:
	float measure(Osciloscope & osciloscope);
	
};

