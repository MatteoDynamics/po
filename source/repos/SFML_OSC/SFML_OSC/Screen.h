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
    int numPoints = 1000;             // Liczba punktów fali sinusoidalnej

public:
    Screen()
    {
       
        screen.setSize(sf::Vector2f(1440, 800));
        screen.setFillColor(sf::Color::Black);
        screen.setOutlineColor(sf::Color::White);
        screen.setOutlineThickness(5);
        screen.setPosition(50, 135);

        gridsize = 50; // Set the size of the grid
        grid.setPrimitiveType(sf::Lines);

        sf::Vector2f screenPosition = screen.getPosition();
        sf::Vector2f screenSize = screen.getSize();

        // Create vertical lines
        for (float x = screenPosition.x; x <= screenPosition.x + screenSize.x; x += gridsize)
        {
            grid.append(sf::Vertex(sf::Vector2f(x, screenPosition.y), sf::Color(255, 255, 255, 50)));
            grid.append(sf::Vertex(sf::Vector2f(x, screenPosition.y + screenSize.y), sf::Color(255, 255, 255, 50)));

        }

        // Create horizontal lines
        for (float y = screenPosition.y; y <= screenPosition.y + screenSize.y; y += gridsize)
        {
            grid.append(sf::Vertex(sf::Vector2f(screenPosition.x, y), sf::Color(255, 255, 255, 50)));
            grid.append(sf::Vertex(sf::Vector2f(screenPosition.x + screenSize.x, y), sf::Color(255, 255, 255, 50)));
        }
    
        
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(screen);
        window.draw(grid);
        
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
