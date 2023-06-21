#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ostream>
class Osciloscope;
class Screen
{
    Osciloscope* osciloscope;
    sf::RectangleShape screen;
 //   sf::VertexArray waveform;

    sf::VertexArray grid;
    int gridsize;
    float amplitude = 50.0f;         // Amplituda fali sinusoidalnej
    float frequency = 0.01f;          // Czêstotliwoœæ fali sinusoidalnej
    float waveSpeed = 0.1f;           // Prêdkoœæ poruszania siê fali
    int numPoints = 1440;             // Liczba punktów fali sinusoidalnej

public:
    Screen();
    void draw(sf::RenderWindow& window);
    void save_to_csv(const std::string filename);
    sf::RectangleShape& get_screen();
};
