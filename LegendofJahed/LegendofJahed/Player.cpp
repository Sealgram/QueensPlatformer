#include "CompiledLibraries.h"
#include "Player.h"

using namespace std;

void Player::initVar()
{
	this->aniState = IDLE;
	this->movingRight = { IntRect(96,0,16,16), IntRect(0,32,16,16),IntRect(32,32,16,16) };
	this->movingLeft = {IntRect(64, 32, 16, 16),IntRect(96,32,16,16),IntRect(0, 64, 16, 16)};
	this->movingUp = { IntRect(32,64,16,16), IntRect(64,64,16,16), IntRect(96,64,16,16) };
	this->movingDown = { IntRect(0,0,16,16), IntRect(32,0,16,16), IntRect(64,0,16,16) };
	this->aniController = 0;

	this->walkedOff = false;



}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/Assets/Jahed.png")) 
		cout << "Could not load the player sheet" << endl;
	

}

void Player::initSprite()
{
	this->Jahed.setTexture(this->textureSheet);
	this->currentFrame = IntRect(0, 0, 16, 16);

	this->Jahed.setTextureRect(this->currentFrame);
	this->Jahed.setScale(7.5, 7.5); //Player size


}

void Player::initAnimations()
{

	this->timer.restart();
}

Player::Player()
{
	this->initVar();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

Player::~Player()
{
}

void Player::updateMovement()
{
	//cout << Jahed.getPosition().x << ", " << Jahed.getPosition().y << endl;

	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {

		this->Jahed.move(-5, 0.f); //Player speed
		this->aniState = PLAYER_ANIMATION_STATE::MOVING_LEFT;

	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {

		this->Jahed.move(5.f, 0.f);
		this->aniState = PLAYER_ANIMATION_STATE::MOVING_RIGHT;

	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::W)) {

		this->Jahed.move(0.f, -5.f);
		this->aniState = PLAYER_ANIMATION_STATE::MOVING_UP;

	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S)) {

	this->Jahed.move(0.f, 5.f);
	this->aniState = PLAYER_ANIMATION_STATE::MOVING_DOWN;

	}
	else {
	this->aniState = PLAYER_ANIMATION_STATE::IDLE;
	}
}
const bool& Player::getBkgController()
{
	return this->walkedOff;
}

void Player::updateAnimations()
{
	if (this->aniState == PLAYER_ANIMATION_STATE::IDLE) {

		this->aniController = 0;
		this->currentFrame = IntRect(32, 0, 16, 16); //Front facing idle
		this->Jahed.setTextureRect(this->currentFrame);


	}
	else if (this->aniState == PLAYER_ANIMATION_STATE::MOVING_LEFT) {

		if (this->timer.getElapsedTime().asSeconds() >= 0.1f)
		{

			this->currentFrame = movingLeft.at(this->aniController);

			if (this->aniController >= 2)
				this->aniController = 0;

			this->aniController++;
			this->timer.restart();
			this->Jahed.setTextureRect(this->currentFrame);

		}

	}
	else if (this->aniState == PLAYER_ANIMATION_STATE::MOVING_RIGHT) {

		if (this->timer.getElapsedTime().asSeconds() >= 0.1f) {

			this->currentFrame = movingRight.at(this->aniController);

			if (this->aniController >= 2)
				this->aniController = 0;

			this->aniController++;
			this->timer.restart();
			this->Jahed.setTextureRect(this->currentFrame);

		}

	}
	else if (this->aniState == PLAYER_ANIMATION_STATE::MOVING_UP) {

		if (this->timer.getElapsedTime().asSeconds() >= 0.1f)
		{

			this->currentFrame = movingUp.at(this->aniController);

			if (this->aniController >= 2)
				this->aniController = 0;

			this->aniController++;
			this->timer.restart();
			this->Jahed.setTextureRect(this->currentFrame);

		}

	}
	else if (this->aniState == PLAYER_ANIMATION_STATE::MOVING_DOWN) {

		if (this->timer.getElapsedTime().asSeconds() >= 0.1f)
		{

			this->currentFrame = movingDown.at(this->aniController);

			if (this->aniController >= 2)
				this->aniController = 0;

			this->aniController++;
			this->timer.restart();
			this->Jahed.setTextureRect(this->currentFrame);

		}

	}
	else {
		this->timer.restart();
	}
}

void Player::updateWindowBoundsCollision()
{
	//Left
	FloatRect JahedPos = this->Jahed.getGlobalBounds();
	//left
	if (JahedPos.left <= 0.f)
		this->Jahed.setPosition(0.f, JahedPos.top);
	else if (JahedPos.left + JahedPos.width >= mapWidth)//right

		this->Jahed.setPosition(mapWidth - JahedPos.width, JahedPos.top);

	if (JahedPos.top <= 0.f - JahedPos.height) {
		this->Jahed.setPosition(JahedPos.left, mapHeight);
		this->walkedOff = true;

	}
	if (JahedPos.top >= mapHeight) {
		this->Jahed.setPosition(JahedPos.left, 0.f);
		this->walkedOff = true;
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updateWindowBoundsCollision();
}

void Player::render(RenderTarget& target)
{

	target.draw(this->Jahed);
}

const Vector2f Player::getPosition()
{
	return this->Jahed.getPosition();
}

void Player::resetBkgController()
{
	this->walkedOff = false;
}


