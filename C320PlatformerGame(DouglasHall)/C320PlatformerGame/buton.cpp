#include "stdafx.h"
#include"buton.h"


Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) {
	this->buttonState = BTN_IDLE;

	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(x, y));
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);


	this->text.setPosition(this->shape.getPosition().x/2.f - this->text.getGlobalBounds().width/2.f, this->shape.getPosition().y / 2.f - this->text.getGlobalBounds().height / 2.f);


	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;



}

Button::~Button() {

}

const bool Button::isPressed() const
{	
	if(this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}



void Button::update(sf::Vector2i mousePos){

	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
		this->buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_ACTIVE;
		}

	}
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}

}

void Button::render(sf::RenderTarget& target) {
	target.draw(this->shape);
}