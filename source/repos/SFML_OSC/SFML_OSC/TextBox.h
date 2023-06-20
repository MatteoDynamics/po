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
		text_counter = 0;
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

		//CONVERT sf::Text to float
		
		//textbox.setString("");


		for (int i = 0; i < text_counter; i++)
		{
			window.draw(texts[i]);
		}
		//std::cout << "text"<<text<<std::endl;
		//this->floatValue = std::stof(text);
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
	float text_to_float()
	{
		return floatValue;
	}

	float save_to_float()
	{
		float floatValue;
		std::istringstream iss(textbox.getString());
		iss >> floatValue;
		return floatValue;
	}

	bool isselected()
	{
		if (isSelected == true)
		{
			std::cout << "isSelected";
			return true;
		}
		else return false;
	}
	void flush_bufor()
	{
		textbox.setString("");
	}
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

