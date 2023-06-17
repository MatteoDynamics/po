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


    float amplitude = 50.0f;         // Amplituda fali sinusoidalnej
    float frequency = 0.01f;          // Czêstotliwoœæ fali sinusoidalnej
    float waveSpeed = 0.1f;           // Prêdkoœæ poruszania siê fali
    int numPoints = 1000;             // Liczba punktów fali sinusoidalnej

public:
    Screen()
    {
        screen.setSize(sf::Vector2f(1440, 810));
        screen.setFillColor(sf::Color::Black);
        screen.setOutlineColor(sf::Color::White);
        screen.setOutlineThickness(5);
        screen.setPosition(50, 135);

        
        
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(screen);
       // window.draw(waveform);
    }

    void save_to_csv(const std::string filename)
    {
        
    }
    sf::RectangleShape& get_screen()
    {
        return screen;
    }
};
