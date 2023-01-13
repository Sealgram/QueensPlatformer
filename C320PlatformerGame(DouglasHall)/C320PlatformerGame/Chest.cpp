#include "stdafx.h"
#include "Chest.h"

void Chest::initVariables()
{
	this->sprite.setTexture(textureSheet);
	this->animState = CHEST_ANIMATION_STATES::CLOSED;
	this->opening = { sf::IntRect(0, 16, 16, 16), sf::IntRect(0, 32, 16, 16), sf::IntRect(0, 48, 16, 16) };
}

void Chest::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/Chest.png"))
	{
		std::cout << "ERROR::CHEST::INITTEXTURE::Could not load the chest sheet." << "\n";
	}
}

void Chest::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 16, 16);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(5.f, 5.f);
	this->sprite.setPosition(925, 130);
}

void Chest::initAnimations()
{
	this->animationTimer.restart();
	// Default movement state
	this->animState = CHEST_ANIMATION_STATES::CLOSED;
}

// Constructor
Chest::Chest()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

// Accessors
const sf::FloatRect Chest::getGlobalBounds() 
{
	return this->sprite.getGlobalBounds();
}

const bool& Chest::getAnimSwitch()
{
	bool animSwitcher = this->animSwitch;

	if (this->animSwitch)
	{
		this->animSwitch = false;
	}

	return animSwitcher;
}

const sf::Vector2f Chest::getPosition()
{
	return this->sprite.getPosition();
}

// Modifiers
void Chest::setAnimState(int animStateIn)
{
	if (animStateIn == 0) {
		this->animState = CHEST_ANIMATION_STATES::CLOSED;
	}
	else if (animStateIn == 1) 
	{
		this->animState = CHEST_ANIMATION_STATES::OPENING;
	}
	else if (animStateIn == 2) {
		this->animState = CHEST_ANIMATION_STATES::OPEN;
	}
}

// Functions
void Chest::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animSwitch = true;
}

void Chest::updateAnimations()
{
	if (this->animState == CHEST_ANIMATION_STATES::OPENING) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.5f || this->getAnimSwitch()) {
			this->currentFrame = opening.at(this->animController);
			if (this->animController >= 2) {
				this->animController = 0;
			}
			this->animController++;
			this->animationTimer.restart();
			std::cout << this->currentFrame.left << ", " << this->currentFrame.top << ", " << this->currentFrame.width << ", " << this->currentFrame.height << "\n";
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == CHEST_ANIMATION_STATES::OPEN) {
		this->currentFrame = sf::IntRect(48, 0, 16, 16);
		this->sprite.setTextureRect(this->currentFrame);
	}
}

void Chest::update() 
{
	this->updateAnimations();
}

void Chest::render(sf::RenderTarget& target) 
{
	target.draw(this->sprite);
}
