#include "Freqmeter.h"
#include "Osciloscope.h"

float Freqmeter::measure(Osciloscope& osciloscope)
{
	Multimetr::set_measured(osciloscope.get_freq());
	std::cout << get_measured();
	return Multimetr::get_measured();
}