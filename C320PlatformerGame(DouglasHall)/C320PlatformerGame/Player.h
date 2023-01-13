#pragma once
#include "stdafx.h"

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, FALLING};

class Player
{
private:
	// Private variables
	sf::Sprite sprite;
	sf::Texture textureSheet;

	// Animation
	short animState;
	sf::IntRect currentFrame;
	bool animSwitch;
	sf::Clock animationTimer;
	std::vector<sf::IntRect> rightFrames;
	std::vector<sf::IntRect> leftFrames;
	int animController;

	// Physics
	sf::Vector2f velocity;
	float maxVelocity;
	float minVelocity;
	float maxVelocityVert;
	float jumpVelocity;
	float acceleration;
	float drag;
	float gravity;

	// Private Functions
    void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

public:
	// Constructor
	Player();

	// Accessors
	const bool& getAnimSwitch();
	const sf::FloatRect getGlobalBounds();
	const sf::Vector2f getPosition();

	// Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();

	// Functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};

