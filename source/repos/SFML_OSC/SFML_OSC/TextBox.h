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
	TextBox(sf::Color color, int size, bool sel)
	{
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;
		if (sel)
		{
			textbox.setString("_");
		}
		else
		{
			textbox.setString("");
		}
	}
	void setFont(sf::Font& font)
	{
		textbox.setFont(font);
	}
	void setPosiiton(sf::Vector2f pos)
	{
		textbox.setPosition(pos);
	}
	void setLimit(bool toF)
	{
		hasLimit = toF;
	}
	void setLimit(bool toF, int lim)
	{
		hasLimit = toF;
		limit = lim-1; 
	}

	void setSelected(bool sel)
	{
		isSelected = sel;
		if (!sel)
		{
			std::string t = text.str();
			std::string newText = "";
			for (int i = 0; i < t.length(); i++)
			{
				newText += t[i];
			}
			textbox.setString(newText);
		}
	}
	std::string getText()
	{
		return text.str();
	}
	void draw(sf::RenderWindow& window)
	{
		 
		window.draw(textbox);
	}
	void typedOn(sf::Event &input_text)
	{
		if (isSelected)
		{
			int chartype = input_text.text.unicode;
			if (chartype < 128)
			{
				if (hasLimit)
				{
					if (text.str().length() <= limit)
					{  
						input(chartype);
					}
					else if (text.str().length() >= limit && chartype == DELETE)
					{
						delete_character();
					}
					
				}
				else {
					input(chartype);
				}
			}
		}
	}

private:
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;
	void input(int type)
	{
		if (type != DELETE && type != ESC && type != ENTER)
		{
			text << static_cast<char>(type);
		}
		else if (type == DELETE)
		{
			if (text.str().length() > 0)
			{
				delete_character();
			}
		}
		textbox.setString(text.str() + "_");
		sf::sleep(sf::microseconds(500));
		textbox.setString(text.str() + "");
		sf::sleep(sf::microseconds(500));
		textbox.setString(text.str() + "_");
	}
	void delete_character()
	{
		std::string t = text.str();
		std::string newText = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newText += t[i];
		}
		text.str("");
		text << newText;
		textbox.setString(text.str());
	}
};

