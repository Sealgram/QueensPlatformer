#include "stdafx.h"
#include "Player.h"

// Private Functions
void Player::initVariables(){
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	this->rightFrames = { sf::IntRect(96, 0, 32, 32), sf::IntRect(0, 32, 32, 32), sf::IntRect(32, 32, 32, 32), sf::IntRect(96, 0, 32, 32), sf::IntRect(0, 32, 32, 32), sf::IntRect(32, 32, 32, 32) };
	this->leftFrames = { sf::IntRect(0, 64, 32, 32), sf::IntRect(96, 32, 32, 32), sf::IntRect(64, 32, 32, 32), sf::IntRect(0, 64, 32, 32), sf::IntRect(96, 32, 32, 32), sf::IntRect(64, 32, 32, 32) };
	this->upFrames = { sf::IntRect(32, 64, 32, 32), sf::IntRect(64, 64, 32, 32), sf::IntRect(96, 64, 32, 32), sf::IntRect(32, 64, 32, 32), sf::IntRect(64, 64, 32, 32), sf::IntRect(96, 64, 32, 32) };
	this->downFrames = { sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 32), sf::IntRect(0, 0, 32, 32), sf::IntRect(32, 0, 32, 32), sf::IntRect(64, 0, 32, 32) };
	this->animController = 0;
	this->animController = 0;
	this->jumping = false;
	this->maxJump = 0.0f;
	this->curJump = 0.0f;
	this->falling = false;
}

void Player::initTexture() {
	if (!this->textureSheet.loadFromFile("Textures/Jahed.png")) {
		std::cout << "ERROR::PLATER::Could not load the player sheet." << "\n";
	}
}

void Player::initSprite() {
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(32, 10, 32, 32);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(5.f, 5.f);
	this->sprite.setPosition(0.0f,500.0f);
}

void Player::initAnimations(){
	this->animationTimer.restart();
}

// Constructors & Destructors
Player::Player() {
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

Player::~Player() {

}

// Public Functions
void Player::updatePhysics() {

}

void Player::collisions(){

}

void Player::updateMovement() {
	// Default movement state
	this->animState = PLAYER_ANIMATION_STATES::IDLE;

	// Other movement states
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { // Moving left
		this->sprite.move(-4.f, 0.0f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { // Moving right
		this->sprite.move(4.f, 0.0f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		this->sprite.move(0.0f,-4.0f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		this->sprite.move(0.0f,4.0f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_DOWN;
	}
	//else if (){
	
	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !this->jumping){
		this->maxJump = 100.0f;
		this->jumping = true;
	}else if(this->jumping == true){
		if(this->curJump < this->maxJump){
			if(this->curJump >= this->maxJump/2.f){
				this->sprite.move(0.0f,2.f);
				this->curJump += 2.f;
			}else{
				this->sprite.move(0.0f,-2.f);
				this->curJump += 2.f;
			}
		}else{
			this->curJump =  0.0f;
			this->maxJump = 0.0f;
			this->jumping = false;
		}
	}*/
}

void Player::updateAnimations(){
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE) {
		this->currentFrame = sf::IntRect(32, 0, 32, 32);
		this->sprite.setTextureRect(this->currentFrame);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame = rightFrames.at(this->animController);
			if (this->animController >= 5) {
				this->animController = 0;
			}
			this->animController++;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame = leftFrames.at(this->animController);
			if (this->animController >= 5) {
				this->animController = 0;
			}
			this->animController++;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if(this->animState == PLAYER_ANIMATION_STATES::MOVING_UP) {
		if(this->animationTimer.getElapsedTime().asSeconds() >= 0.1f){
			this->currentFrame = upFrames.at(this->animController);
			if(this->animController >= 5){
				this->animController = 0;
			}
			this->animController++;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if(this->animState == PLAYER_ANIMATION_STATES::MOVING_DOWN) {
		if(this->animationTimer.getElapsedTime().asSeconds() >= 0.1f){
			this->currentFrame = downFrames.at(this->animController);
			if(this->animController >= 5){
				this->animController = 0;
			}
			this->animController++;
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else {
		this->animationTimer.restart();
	}
}

void Player::update() {
	this->updateMovement();
	this->updateAnimations();
}

void Player::render(sf::RenderTarget& target){
	target.draw(this->sprite);
}
