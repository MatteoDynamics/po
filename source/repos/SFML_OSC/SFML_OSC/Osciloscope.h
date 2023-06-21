#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
class Screen;
class Osciloscope
{
    int wave_count;
    sf::VertexArray *waveforms;
	sf::VertexArray waveform;
    sf::RectangleShape * screen;

    float amplitude = 50.0;         // Amplituda fali sinusoidalnej
    float frequency = 0.05;          // Czêstotliwoœæ fali sinusoidalnej
    float waveSpeed = 0.1;           // Prêdkoœæ poruszania siê fali
    int numPoints = 1440;             // Liczba punktów fali sinusoidalnej
    void set_waveform(Screen& screen);
public:
    Osciloscope(Screen &screen);
    float get_amp() { return amplitude; };
    float get_freq() { return frequency; };
    void scaling();
    void draw(sf::RenderWindow& window);
    
    void set_amplitude(float amp, Screen& screen);
    void set_frequency(float freq, Screen& screen);
    void save_waveform(const std::string& filename);
    
    //WAVEFORM ALOCATION
    void add_new_function();
};

