#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Button
{
    int button_counter;
    sf::RectangleShape* buttons;
    sf::RectangleShape button;
    sf::Text text; 

public:
    Button();
    Button(std::string t, sf::Vector2f size, int charsize, sf::Color color, sf::Color textcolor);
    void set_font(sf::Font& f1);
    void set_back_color(sf::Color color);

    void set_text_color(sf::Color& color);
    void set_position(sf::Vector2f& pos);
    void drawButton(sf::RenderWindow& window);
    bool is_mouse_on(sf::RenderWindow& window);

    void add_new_button();

};
