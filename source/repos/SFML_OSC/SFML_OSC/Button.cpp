#include "Button.h"
Button::Button(std::string t, sf::Vector2f size, int charsize, sf::Color color, sf::Color textcolor)
{
    buttons = nullptr;
    text.setString(t);
    text.setFillColor(textcolor);
    text.setCharacterSize(charsize);
    button.setSize(size);
    button.setFillColor(color);
}
void Button::set_font(sf::Font& f1)
{
    text.setFont(f1);
}
void Button::set_back_color(sf::Color color)
{
    button.setFillColor(color);
}

void Button::set_text_color(sf::Color& color)
{
    text.setFillColor(color);
}
void Button::set_position(sf::Vector2f& pos)
{
    if (pos.x > 1920 || pos.y > 1080 && pos.x < 0 || pos.y < 0)
    {
        throw std::exception();
    }
    button.setPosition(pos);
    float xPos = (pos.x + button.getGlobalBounds().width / 5.5) - (text.getGlobalBounds().width / 2);
    float yPos = (pos.y + button.getGlobalBounds().height / 5) - (text.getGlobalBounds().height / 2);;
    text.setPosition(xPos, yPos);
}
void Button::drawButton(sf::RenderWindow& window)
{
    window.draw(button);
    window.draw(text);
}
bool Button::is_mouse_on(sf::RenderWindow& window)
{
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    float PosX = button.getPosition().x;
    float PosY = button.getPosition().y;

    float btnPosxWidth = button.getPosition().x + button.getGlobalBounds().width;
    float btnPosyWidth = button.getPosition().y + button.getGlobalBounds().height;
    if (mouseX<btnPosxWidth && mouseX>PosX && mouseY <btnPosyWidth && mouseY> PosY)
    {
        return true;
    }
    else return false;
}

void Button::add_new_button()
{

}