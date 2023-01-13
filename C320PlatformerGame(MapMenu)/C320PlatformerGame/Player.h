#pragma once
#include "stdafx.h"

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING,MOVING_UP,MOVING_DOWN};

class Player
{
private:
	// Private variables
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	std::vector<sf::IntRect> rightFrames;
	std::vector<sf::IntRect> leftFrames;
	std::vector<sf::IntRect> upFrames;
	std::vector<sf::IntRect> downFrames;
	int animController;
	bool jumping;
	float maxJump;
	float curJump;
	bool falling;
	
	//State

	// Animation
	short animState;
	sf::IntRect currentFrame;

	// Physics
	sf::Vector2f velocicy;
	float acceleration;
	float deceleration;

	// Core

	// Private Functions
    void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();

public:
	// Constructors and Destructors
	Player();
	virtual ~Player();

	// Functions
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void collisions();
	void update();
	void render(sf::RenderTarget& target);
};

