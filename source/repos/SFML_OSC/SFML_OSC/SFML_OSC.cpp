#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextBox.h"
#include "Screen.h"
#include "Button.h"
#include "Osciloscope.h"
#include "Multimetr.h"

using namespace std;
constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

int main()
{
    Button* buttons = nullptr;
    int button_counter;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Osciloscope");
    window.setFramerateLimit(60);
    
    sf::Font arial;
    arial.loadFromFile("ARIAL.ttf");

    //SCREEN
    Screen s1;
    Osciloscope osc(s1);
    osc.set_amplitude(250,s1);


    //TEXT INPUT
    TextBox text(sf::Color::Black, 20, false);
    text.setLimit(true, 3);
    text.setFont(arial);
    text.setPosiiton(sf::Vector2f(75, 55));

    //POSITIONS
    sf::Vector2f pos(1600, 100);
    sf::Vector2f pos2(1600, 300);
    sf::Vector2f save_pos(1600, 500);
    sf::Vector2f typein_pos(50, 50);
    sf::Vector2f add_pos(600, 100);

    //BUTTONS
    Button b1("MATH", sf::Vector2f(200, 100), 50, sf::Color::White, sf::Color:: Black);
    b1.set_position(pos);
    b1.set_font(arial);

    Button measure("MEASURE", sf::Vector2f(200, 100), 25, sf::Color::White, sf::Color::Black);
    measure.set_position(pos2);
    measure.set_font(arial);

    Button save_button("SAVE", sf::Vector2f(200, 100), 50, sf::Color::White, sf::Color::Black);
    save_button.set_position(save_pos);
    save_button.set_font(arial);

    Button typein_button("TYPE IN AMPLITUDE:                    TYPE IN FREQUENCY: ",sf::Vector2f(1440, 50), 25, sf::Color::White, sf::Color::Black);
    typein_button.set_position(typein_pos);
    typein_button.set_font(arial);


    while (window.isOpen())
    {
        sf::Event event;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash))
        {
            text.setSelected(true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            osc.set_amplitude(text.save_to_float(), s1);
            
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
                    window.close(); //CLOSE EVENT

                }

                case sf::Event::TextEntered:
                {
                    text.typedOn(event);
                   // osc.set_amplitude(text.text_to_float(), s1);//TYPING EVENT
                }

                case sf::Event::MouseMoved:
                {
                    if (b1.is_mouse_on(window))
                    {
                        b1.set_back_color(sf::Color::Yellow); // MOUSE ON BUTTON
                    }
                    else
                    {
                        b1.set_back_color(sf::Color::White); // MOUSE NOT ON BUTTON
                    }
                    if (save_button.is_mouse_on(window))
                    {
                        save_button.set_back_color(sf::Color::Yellow); // MOUSE ON BUTTON
                    }
                    else
                    {
                        save_button.set_back_color(sf::Color::White); // MOUSE NOT ON BUTTON
                    }
                }break;

                case sf::Event::MouseButtonPressed:
                {
                    if (b1.is_mouse_on(window))
                    {
                        std::cout << "Opened math" << std::endl; // PRESSING TEST
                        sf::RenderWindow window_Math(sf::VideoMode(800, 600), "Multimeter");
                        Button add_button("ADD", sf::Vector2f(200, 100), 50, sf::Color::White, sf::Color::Black);
                        add_button.set_position(add_pos);
                        add_button.set_font(arial);
                        while (window_Math.isOpen())
                        {
                            sf::Event event2;
                            while (window_Math.pollEvent(event2))
                            {
                                switch (event2.type)
                                {
                                case sf::Event::Closed:
                                    window_Math.close();
                                    break;
                                case sf::Event::MouseMoved:
                                {
                                    if (add_button.is_mouse_on(window_Math))
                                    {
                                        add_button.set_back_color(sf::Color::Yellow); // MOUSE ON BUTTON
                                    }
                                    else
                                    {
                                        add_button.set_back_color(sf::Color::White); // MOUSE NOT ON BUTTON
                                    }
                                }break;
                                case sf::Event::MouseButtonPressed:
                                {
                                    if (add_button.is_mouse_on(window_Math))
                                    {
                                        TextBox text2(sf::Color::White, 20, true);
                                        text2.setLimit(true, 10);
                                        text2.setFont(arial);
                                        text2.setPosiiton(sf::Vector2f(75, 55));
                                        osc.add_new_function();
                                        text2.draw(window_Math);
                                        /*t1.add_newText();*/
                                        std::cout << "win2 dziala" << std::endl;
                                    }
                                }
                                }
                            }
                           
                            window_Math.clear();
                            add_button.drawButton(window_Math);
                            window_Math.display();
                        }
                    }
                    if (save_button.is_mouse_on(window))
                    {
                        std::cout << "saved";
                        osc.save_waveform("waveform.csv");
                    }
                }
                break;

     
                

            }

        }

        window.clear();
        s1.draw(window);
        
        b1.drawButton(window);
        measure.drawButton(window);
        save_button.drawButton(window);
        typein_button.drawButton(window);
        osc.draw(window);
        text.draw(window);
      
        window.display();

    }

    return 0;
}

