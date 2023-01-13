#pragma once
#include "Player.h"

class Game
{
private:
	// Window
	sf::RenderWindow window;
	sf::Event ev;
	sf::Texture map;
	sf::Sprite background;
	enum PLAYER_SCREEN_STATES {PLAY =0,MAP};
	short screenState;
	sf::Clock clock;
	sf::Clock clockAnim;
	float iconAnim;
	sf::Sprite spIcon;

	// Private variables
	Player* player;
	
	// Private Functions
	void initWindow();
	void initPlayer();

public:

	// Constructors & Destructors 
	Game();
	virtual ~Game();

	// Functions
	void openMap();
	void setUpMap();
	void updatePlayer();
	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;
};

