#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Osciloscope;
class Screen
{
    Osciloscope* osciloscope;
    sf::RectangleShape screen;
    sf::VertexArray waveform;

    float amplitude = 50.0f;         // Amplituda fali sinusoidalnej
    float frequency = 0.02f;          // Czêstotliwoœæ fali sinusoidalnej
    float waveSpeed = 0.1f;           // Prêdkoœæ poruszania siê fali
    int numPoints = 1000;             // Liczba punktów fali sinusoidalnej

public:
    Screen()
    {
        screen.setSize(sf::Vector2f(1440, 810));
        screen.setFillColor(sf::Color::Black);
        screen.setOutlineThickness(5);
        screen.setOutlineColor(sf::Color::White);
        screen.setPosition(50, 135);

        waveform.setPrimitiveType(sf::LinesStrip);
        waveform.resize(numPoints);
        for (int i = 0; i < numPoints; ++i)
        {
            float x = static_cast<float>(i) / numPoints * screen.getSize().x;
            float y = sin(x);
            waveform[i].position = sf::Vector2f(screen.getPosition().x + x, screen.getPosition().y + screen.getSize().y * 0.5f - y);
            waveform[i].color = sf::Color::Yellow;
        }
        
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(screen);
        window.draw(waveform);
    }
};
