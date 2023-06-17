#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextBox.h"
#include "Screen.h"
#include "Button.h"
#include "Osciloscope.h"
using namespace std;
constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Osciloscope");
    window.setFramerateLimit(60);
    //  window.setKeyRepeatEnabled(true);
    Osciloscope osc;
    sf::Font arial;
    arial.loadFromFile("ARIAL.ttf");
    Screen s1;
    TextBox text(sf::Color::White, 20, false);
    text.setLimit(true, 10);
    std::string add = "add";
    sf::Vector2f vec = { 100, 200 };
    text.setFont(arial);
    text.setPosiiton(sf::Vector2f(1700, 100));
    sf::Vector2f pos(1600, 100);
    sf::Vector2f pos2(1600, 300);
    Button b1("MATH", sf::Vector2f(200, 100), 50, sf::Color::White, sf::Color:: Black);
    b1.set_position(pos);
    b1.set_font(arial);

    Button b2("MEASURE", sf::Vector2f(200, 100), 25, sf::Color::White, sf::Color::Black);
    b2.set_position(pos2);
    b2.set_font(arial);
    while (window.isOpen())
    {
        sf::Event event;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            text.setSelected(true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            text.setSelected(false);
        }
        
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();

                }

                case sf::Event::TextEntered:
                {
                    text.typedOn(event);
                }

                case sf::Event::MouseMoved:
                {
                    if (b1.is_mouse_on(window))
                    {
                        b1.set_back_color(sf::Color::Yellow);
                    }
                    else
                    {
                        b1.set_back_color(sf::Color::White);
                    }
                }break;

                case sf::Event::MouseButtonPressed:
                {
                    if (b1.is_mouse_on(window))
                    {
                    std:; cout << "Works" << std::endl;
                    }
                }break;

     
                

            }

       
           // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        //    {
          //      window.close();
        //    }
           // if (sf::Mouse::getPosition(window)<sf::Vector2f)
            //{

            //}
        }

        window.clear();
        s1.draw(window);
        text.draw(window);
        b1.drawButton(window);
        b2.drawButton(window);
      //  osc.draw(window);
        window.display();
    }

    return 0;
}
