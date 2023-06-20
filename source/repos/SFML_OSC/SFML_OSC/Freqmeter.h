#pragma once
#include "Multimetr.h"
class Freqmeter:public Multimetr
{
public:
	float measure(Osciloscope& osciloscope);
};

