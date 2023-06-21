#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <SFML/System.hpp>


#define DELETE 8
#define ENTER 13
#define	ESC 27
class TextBox
{
public:

	TextBox();
	TextBox(sf::Color color, int size, bool sel);
	void setFont(sf::Font& font);
	void setPosiiton(sf::Vector2f pos);
	void setLimit(bool toF);
	void setLimit(bool toF, int lim);

	void setSelected(bool sel);
	std::string getText();
	void draw(sf::RenderWindow& window);
	void typedOn(sf::Event& input_text);
	
	float text_to_float();

	float save_to_float();
	bool isselected();
	void flush_bufor();
	//void add_newText(const std::string &name)
	//{
	//	text_counter++;
	//	sf::Text* tmp = new sf::Text[text_counter];
	//	for (int i = 0; i < text_counter - 1; i++)
	//	{
	//		tmp[i] = texts[i];
	//	}
	//	delete[] texts;
	//	texts = tmp;

	//	// Set properties of the new sf::Text object
	//	texts[text_counter - 1].setFillColor(sf::Color::White);
	//	texts[text_counter - 1].setCharacterSize(25);
	//	texts[text_counter - 1].setStyle(sf::Text::Bold);
	//	texts[text_counter - 1].setPosition(100, 100);
	//}


private:
	int text_counter;
	sf::Text* texts;
	float floatValue;
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;
	void input(int type);
	void delete_character();

};

