#include "stdafx.h"
#include "Player.h"

// Private Functions
void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	this->rightFrames = { sf::IntRect(96, 0, 16, 16), sf::IntRect(0, 32, 16, 16), sf::IntRect(32, 32, 16, 16), sf::IntRect(96, 0, 16, 16), sf::IntRect(0, 32, 16, 16), sf::IntRect(32, 32, 16, 16) };
	this->leftFrames = { sf::IntRect(0, 64, 16, 16), sf::IntRect(96, 32, 16, 16), sf::IntRect(64, 32, 16, 16), sf::IntRect(0, 64, 16, 16), sf::IntRect(96, 32, 16, 16), sf::IntRect(64, 32, 16, 16) };
	this->animController = 0;
}

void Player::initTexture() 
{
	if (!this->textureSheet.loadFromFile("Textures/Jahed.png")) 
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load the player sheet." << "\n";
	}
}

void Player::initSprite() 
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(32, 0, 16, 16);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(5.f, 5.f);
	this->sprite.setPosition(920, 952);
}

void Player::initAnimations() 
{
	this->animationTimer.restart();
	this->animSwitch = true;
}

void Player::initPhysics() 
{
	this->maxVelocity = 15.f;
	this->minVelocity = 1.f;
	this->maxVelocityVert = 15.f;
	this->jumpVelocity = 80.f;
	this->acceleration = 3.f;
	this->drag = 0.85f;
	this->gravity = 2.f;
}

// Constructors & Destructors
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

// Accessors
const bool& Player::getAnimSwitch() 
{
	bool animSwitcher = this->animSwitch;

	if (this->animSwitch) 
	{
		this->animSwitch = false;
	}

	return animSwitcher;
}

const sf::FloatRect Player::getGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Player::getPosition()
{
	return this->sprite.getPosition();
}

// Modifiers
void Player::setPosition(const float x, const float y) 
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY() 
{
	this->velocity.y = 0.f;
}

// Public Functions
void Player::resetAnimationTimer() 
{
	this->animationTimer.restart();
	this->animSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	// Accelleration
	this->velocity.x += dir_x * this->acceleration;

	// Jumping
	if (dir_y > 0) {
		this->velocity.y -= dir_y;
	}

	// Velocity limiting
	if (std::abs(this->velocity.x) > this->maxVelocity) 
	{
		this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::updatePhysics() 
{
	// Gravity
	this->velocity.y += 1.0 * this->gravity;
	if (this->velocity.y > this->maxVelocityVert) 
	{
		this->velocity.y = this->maxVelocityVert * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	// Deceleration
	this->velocity *= this->drag;

	// Limit Deceleration
	if (std::abs(this->velocity.x) < this->minVelocity) 
	{
		this->velocity.x = 0.f;
	}
	/*if (std::abs(this->velocity.y) < this->minVelocity && std::abs(this->velocity.y) > 0)
	{
		this->velocity.y = 0.f;
	}*/

	this->sprite.move(this->velocity);
}

void Player::updateMovement() 
{
	// Default movement state
	this->animState = PLAYER_ANIMATION_STATES::IDLE;

	// Other movement states
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->velocity.y != 0) 
	{ // Moving right while falling
		this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::FALLING;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->velocity.y != 0) 
	{ // Moving left while falling
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::FALLING;
	}
	else if (this->velocity.y != 0) 
	{ // Falling
		this->animState = PLAYER_ANIMATION_STATES::FALLING;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{ // Moving right
		this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{ // Moving left
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
	{ // Jumping
		this->move(0.f, jumpVelocity);
		this->animState = PLAYER_ANIMATION_STATES::FALLING;
	}
}

void Player::updateAnimations(){
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		this->currentFrame = sf::IntRect(32, 0, 16, 16);
		this->sprite.setTextureRect(this->currentFrame);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT) 
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
			this->currentFrame = rightFrames.at(this->animController);
			if (this->animController >= 5) {
				this->animController = 0;
			}
			this->animController++;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT) 
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
			this->currentFrame = leftFrames.at(this->animController);
			if (this->animController >= 5) {
				this->animController = 0;
			}
			this->animController++;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::FALLING) 
	{
		this->currentFrame = sf::IntRect(64, 0, 16, 16);
		this->sprite.setTextureRect(this->currentFrame);
	}
	else
	{
		this->animationTimer.restart();
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
	// std::cout << this->sprite.getPosition().x << ", " << this->sprite.getPosition().y << "\n";
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
