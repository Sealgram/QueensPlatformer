#pragma once
#include "Player.h"
#include "Chest.h"

class Game
{
private:
	// Window
	sf::RenderWindow window;
	sf::Event ev;

	// Background
	sf::Sprite background;
	sf::Texture backgroundTexture;

	// Text display
	sf::Font font;
	sf::Text timer;
	sf::Text tips;

	// Win screen
	sf::Text win;
	sf::Text winTimerDisplay;
	sf::Sprite winScreen;
	sf::Texture winTexture;
	bool gameWin;


	// Private variables
	Player* player;
	Chest* chest;
	sf::Clock completionTimer;
	bool hasKey;
	float timeatKeyGain;
	float timeatCompletion;
	bool chestLocked;
	bool chestCollision;
	
	// Private Functions
	void initWindow();
	void initPlayer();
	void initChest();
	void initFonts();
	void initText();
	void initBackground();
	void initWinScreen();
	bool inRange(unsigned low, unsigned high, unsigned x);

public:

	// Constructors & Destructors 
	Game();
	virtual ~Game();

	// Functions
	void updatePlayer();
	void updateChest();
	void updateCollision();
	void updateGUI();
	void updateWinScreen();
	void update();
	void renderPlayer();
	void renderChest();
	void renderBackground();
	void renderGUI();
	void renderWinScreen();
	void render();
	const sf::RenderWindow& getWindow() const;
};

