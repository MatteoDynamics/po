#include "Voltmeter.h"
#include "Osciloscope.h"

float Voltmeter::measure(Osciloscope &osciloscope)
{
	Multimetr::set_measured(osciloscope.get_amp());
	return Multimetr::get_measured();
}