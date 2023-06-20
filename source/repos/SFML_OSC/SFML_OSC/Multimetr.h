#pragma once
class Osciloscope;
class Multimetr
{
	Osciloscope* osciloscope;
	float measured;
public:
	virtual float measure(Osciloscope& osciloscope) = 0;
	void set_measured(float meas) { measured = meas; };
	float get_measured() { return measured; };
};

