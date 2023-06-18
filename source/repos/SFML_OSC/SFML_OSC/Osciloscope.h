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

public:
    Osciloscope(Screen &screen);
    void draw(sf::RenderWindow& window)
    {
        window.draw(waveform);
    }
    void set_waveform(Screen& screen);
    void set_amplitude(float amp, Screen& screen)
    {
        amplitude = amp;
        set_waveform(screen);
        std::cout << "osc amp: " << amplitude << std::endl;
    }
    void save_waveform(const std::string& filename);
    
    //WAVEFORM ALOCATION
    void add_new_function()
    {
        if (wave_count >= 3)
        {
            std::cerr<< "Max wave_count is 3" << std::endl;
            return;
        }
        wave_count++;
        sf::VertexArray* tmp;
        tmp = new sf::VertexArray[wave_count];
        if (tmp == NULL)
        {
            std::cerr << "Not enough memory" << std::endl;
            return;
        }
        for (int i = 0; i < wave_count-1; i++)
        {
            tmp[i] = waveforms[i];
        }
        delete[] waveforms;
        waveforms = tmp;
        
    }
};

