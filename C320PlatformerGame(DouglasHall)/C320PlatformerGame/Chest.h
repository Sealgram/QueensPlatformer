#pragma once
#include "stdafx.h"

enum CHEST_ANIMATION_STATES {CLOSED = 0, OPENING, OPEN};

class Chest
{
private:
	// Private variables
	sf::Sprite sprite;
	sf::Texture textureSheet;

	// Animation
	short animState;
	sf::IntRect currentFrame;
	bool animSwitch;
	std::vector<sf::IntRect> opening;
	sf::Clock animationTimer;
	int animController;

	// Private functions
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
public:
	// Constructor
	Chest();

	// Accessors
	const sf::FloatRect getGlobalBounds();
	const bool& getAnimSwitch();
	const sf::Vector2f getPosition();

	// Modifiers
	void setAnimState(int animStateIn);

	// Functions
	void resetAnimationTimer();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};

