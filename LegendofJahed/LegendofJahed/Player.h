#pragma once

using namespace sf;
using namespace std;

enum PLAYER_ANIMATION_STATE {IDLE = 0, MOVING_LEFT, MOVING_RIGHT,MOVING_UP, MOVING_DOWN};

class Player
{

private:
	Sprite Jahed;
	Texture textureSheet;

	bool walkedOff;

	int aniController;

	//Animation
	short aniState;
	IntRect currentFrame;

	//Movement
	bool isMoving;
	Clock timer;
	vector<IntRect> movingRight;
	vector<IntRect> movingLeft;
	vector<IntRect> movingUp;
	vector<IntRect> movingDown;

	//Core
	void initVar();
	void initTexture();
	void initSprite();
	void initAnimations();


public:
	Player();
	const bool& getBkgController();
	virtual ~Player();

	const Vector2f getPosition();

	//Fucntions
	void resetBkgController();
	void updateMovement();
	void updateAnimations();
	void updateWindowBoundsCollision();
	void update();
	void render(RenderTarget& target);

	float mapWidth = 1920.f;
	float mapHeight = 1080.f;
};

