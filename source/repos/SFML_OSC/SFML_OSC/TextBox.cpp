#include "TextBox.h"
void TextBox::input(int type)
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
void TextBox::delete_character()
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

TextBox::TextBox(sf::Color color, int size, bool sel)
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
void TextBox::setFont(sf::Font& font)
{
	textbox.setFont(font);
}
void TextBox::setPosiiton(sf::Vector2f pos)
{
	textbox.setPosition(pos);
}
void TextBox::setLimit(bool toF)
{
	hasLimit = toF;
}
void TextBox::setLimit(bool toF, int lim)
{
	hasLimit = toF;
	limit = lim - 1;
}

void TextBox::setSelected(bool sel)
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
std::string TextBox::getText()
{
	return text.str();
}
void TextBox::draw(sf::RenderWindow& window)
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
void TextBox::typedOn(sf::Event& input_text)
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
float TextBox::text_to_float()
{
	return floatValue;
}

float TextBox::save_to_float()
{
	float floatValue;
	std::istringstream iss(textbox.getString());
	iss >> floatValue;
	return floatValue;
}

bool TextBox::isselected()
{
	if (isSelected == true)
	{
		std::cout << "isSelected";
		return true;
	}
	else return false;
}
void TextBox::flush_bufor()
{
	textbox.setString("");
}