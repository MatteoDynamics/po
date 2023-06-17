#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
class Screen;
class Osciloscope
{
	sf::VertexArray waveform;
    sf::RectangleShape * screen;

    float amplitude = 50.0;         // Amplituda fali sinusoidalnej
    float frequency = 0.05;          // Cz�stotliwo�� fali sinusoidalnej
    float waveSpeed = 0.1;           // Pr�dko�� poruszania si� fali
    int numPoints = 1000;             // Liczba punkt�w fali sinusoidalnej

public:
    Osciloscope(Screen &screen);
    void draw(sf::RenderWindow& window)
    {
        window.draw(waveform);
    }
    void set_waveform(Screen& screen);
    void set_amplitude(int amp, Screen& screen)
    {
        amplitude = amp;
        set_waveform(screen);
    }
};

