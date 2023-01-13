#include "stdafx.h"
#include "Game.h"

// Private functions
void Game::initWindow()
{
	// Initializing the window
	this->window.create(sf::VideoMode::VideoMode(1920, 1080), "Douglas Library", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
	this->completionTimer.restart();
}

void Game::initPlayer() 
{
	this->player = new Player();
	this->hasKey = false;
}

void Game::initChest()
{
	this->chest = new Chest();
	this->chestLocked = true;
	this->chestCollision = false;
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("PixellettersFull.ttf")) 
	{
		std::cout << "ERROR::GAME::INITFONTS::Could not load PixellettersFull.ttf." << "\n";
	}
}

void Game::initText()
{
	// Timer text variables
	this->timer.setFont(this->font);
	this->timer.setFillColor(sf::Color::White);
	this->timer.setCharacterSize(48);
	this->timer.setOutlineColor(sf::Color::Black);
	this->timer.setOutlineThickness(2);
	this->timer.setPosition(800, 0);

	// Tips text variables
	this->tips.setFont(this->font);
	this->tips.setFillColor(sf::Color::White);
	this->tips.setCharacterSize(64);
	this->tips.setOutlineColor(sf::Color::Black);
	this->tips.setOutlineThickness(4);
	this->tips.setPosition(0, 1000);

	// Win screen text variables
	this->win.setFont(this->font);
	this->win.setFillColor(sf::Color::White);
	this->win.setCharacterSize(96);
	this->win.setOutlineColor(sf::Color::Black);
	this->win.setOutlineThickness(6);
	this->win.setPosition(480, 340);

	// Win screen timer variables
	this->winTimerDisplay.setFont(this->font);
	this->winTimerDisplay.setFillColor(sf::Color::White);
	this->winTimerDisplay.setCharacterSize(128);
	this->winTimerDisplay.setOutlineColor(sf::Color::Black);
	this->winTimerDisplay.setOutlineThickness(8);
	this->winTimerDisplay.setPosition(640, 600);
}

void Game::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("Textures/DouglasLibrary.png"))
	{
		std::cout << "ERROR::GAME::INITBACKGROUND::Could not load the background texture." << "\n";
	}
	this->background.setTexture(backgroundTexture);
}

void Game::initWinScreen()
{
	if (!this->winTexture.loadFromFile("Textures/win.png"))
	{
		std::cout << "ERROR::GAME::INITWINSCREEN::Could not load the win screen texture." << "\n";
	}
	this->winScreen.setTexture(winTexture);
	this->gameWin = false;
}

bool Game::inRange(unsigned low, unsigned high, unsigned x)
{
	return (low <= x && x <= high);
}

// Constructors & Destructors
Game::Game() 
{
	this->initWindow();
	this->initPlayer();
	this->initChest();
	this->initFonts();
	this->initText();
	this->initBackground();
	this->initWinScreen();
}

Game::~Game() 
{
	delete this->player;
}

// Public functions
void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateChest()
{
	this->chest->update();
}

void Game::updateCollision() {
	// Collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y - 80)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height - 80
		);
	}
	// Collision top of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height < 80)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			80
		);
	}
	// Collision left
	if (this->player->getPosition().x < 0)
	{
		this->player->setPosition(
			0,
			this->player->getPosition().y
		);
	}
	// Collision right
	if (this->player->getPosition().x > this->window.getSize().x - 80)
	{
		this->player->setPosition(
			this->window.getSize().x - 80,
			this->player->getPosition().y
		);
	}
	// Collision left vertical piece
	if (this->inRange(80, 260, this->player->getPosition().y) && this->inRange(1023, 1037, this->player->getPosition().x))
	{
		this->player->setPosition(
			1078,
			this->player->getPosition().y
		);
	}
	// Platform Collision
	if (this->inRange(816, 860, this->player->getPosition().y + this->player->getGlobalBounds().height) && this->inRange(1120, 1264, this->player->getPosition().x))
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			816 - this->player->getGlobalBounds().height
		);
	}
	if (this->inRange(640, 684, this->player->getPosition().y + this->player->getGlobalBounds().height) && this->inRange(1422, 1546, this->player->getPosition().x))
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			640 - this->player->getGlobalBounds().height
		);
	}
	if (this->inRange(388, 432, this->player->getPosition().y + this->player->getGlobalBounds().height) && this->inRange(1198, 1332, this->player->getPosition().x))
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			388 - this->player->getGlobalBounds().height
		);
	}
	if (this->inRange(289, 333, this->player->getPosition().y + this->player->getGlobalBounds().height) && this->inRange(1460, 1879, this->player->getPosition().x))
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			289 - this->player->getGlobalBounds().height
		);
	}
	if (this->inRange(186, 230, this->player->getPosition().y + this->player->getGlobalBounds().height) && this->inRange(1745, 1879, this->player->getPosition().x))
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			186 - this->player->getGlobalBounds().height
		);
	}
	if (this->inRange(830, 874, this->player->getPosition().y + this->player->getGlobalBounds().height) && this->inRange(532, 666, this->player->getPosition().x))
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			830 - this->player->getGlobalBounds().height
		);
	}
	if (this->inRange(701, 745, this->player->getPosition().y + this->player->getGlobalBounds().height) && this->inRange(242, 376, this->player->getPosition().x))
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			701 - this->player->getGlobalBounds().height
		);
	}
	if (this->inRange(540, 584, this->player->getPosition().y + this->player->getGlobalBounds().height) && this->inRange(50, 184, this->player->getPosition().x))
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			540 - this->player->getGlobalBounds().height
		);
	}
	if (this->inRange(372, 416, this->player->getPosition().y + this->player->getGlobalBounds().height) && this->inRange(255, 389, this->player->getPosition().x))
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			372 - this->player->getGlobalBounds().height
		);
	}
	if (this->inRange(267, 311, this->player->getPosition().y + this->player->getGlobalBounds().height) && this->inRange(532, 991, this->player->getPosition().x))
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			267 - this->player->getGlobalBounds().height
		);
	}
	if (this->inRange(215, 259, this->player->getPosition().y + this->player->getGlobalBounds().height) && this->inRange(857, 1037, this->player->getPosition().x))
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			215 - this->player->getGlobalBounds().height
		);
	}
	// Key collision 
	if (this->inRange(
			129, 164, this->player->getPosition().y + (this->player->getGlobalBounds().height / 2)
			) && 
		this->inRange(
			1781, 1844, this->player->getPosition().x
			)
		)
	{
		if (!hasKey) {
			this->hasKey = true;
			this->timeatKeyGain = this->completionTimer.getElapsedTime().asSeconds();
			// std::cout << "Key gained! " << hasKey << " " << timeatKeyGain << "\n";
		}
	}
	// Chest collision
	if (this->inRange(
			this->chest->getPosition().x,
			this->chest->getPosition().x + this->chest->getGlobalBounds().width,
			this->player->getPosition().x + (this->player->getGlobalBounds().width / 2)
			) &&
		this->inRange(
			this->chest->getPosition().y,
			this->chest->getPosition().y + this->chest->getGlobalBounds().height,
			this->player->getPosition().y + (this->player->getGlobalBounds().height / 2)
			)
		)
	{
		if (this->hasKey) 
		{
			this->chestLocked = false;
			this->chestCollision = true;
			this->chest->setAnimState(1);
			if (!this->gameWin) {
				this->timeatCompletion = this->completionTimer.getElapsedTime().asSeconds();
			}
			this->gameWin = true;
		}
		else 
		{
			this->chestCollision = true;
		}
	}
	else {
		this->chestCollision = false;
		if (this->chestLocked) 
		{
			this->chest->setAnimState(0);
		}
		else 
		{
			this->chest->setAnimState(2);
		}
	}
}

void Game::updateGUI()
{
	// Updating the timer
	std::stringstream timerStream;
	timerStream << "Time Elapsed: " << this->completionTimer.getElapsedTime().asSeconds();
	this->timer.setString(timerStream.str());

	// Updating the tip text
	std::stringstream tipStream;
	if (this->completionTimer.getElapsedTime().asSeconds() < 3)
	{
		this->tips.setString("Welcome to Douglas Library!");
	}
	if (this->inRange(3, 7, this->completionTimer.getElapsedTime().asSeconds()))
	{
		this->tips.setString("Objective: Get the key and use it to unlock the cabinet containing the exam results!");
	}
	if (this->completionTimer.getElapsedTime().asSeconds() > 7)
	{
		this->tips.setString("");
	}
	if (this->hasKey && this->inRange(this->timeatKeyGain, this->timeatKeyGain + 5, this->completionTimer.getElapsedTime().asSeconds())) {
		tipStream << "Key obtained at " << this->timeatKeyGain << ". Now go open the chest!";
		this->tips.setString(tipStream.str());
	}
	if (!this->hasKey && this->chestCollision)
	{
		tipStream << "Must obtain the key before opening the chest!";
		this->tips.setString(tipStream.str());
	}
	if (this->gameWin)
	{
		tipStream << "Exam results obtained in " << this->timeatCompletion << "!";
		this->tips.setString(tipStream.str());
	}

}

void Game::updateWinScreen()
{
	this->win.setString("Exam Papers Obtained! Time taken:");
	std::stringstream finalTimerDisplay;
	finalTimerDisplay << this->timeatCompletion << " seconds!";
	this->winTimerDisplay.setString(finalTimerDisplay.str());
}

void Game::update() 
{
	// Polling window events
	while (this->window.pollEvent(this->ev)) 
	{
		if (this->ev.type == sf::Event::Closed) 
		{
			this->window.close();
		}
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) 
		{
			this->window.close();
		}
		if (
			this->ev.type == sf::Event::KeyReleased && (
				this->ev.key.code == sf::Keyboard::W || 
				this->ev.key.code == sf::Keyboard::A || 
				this->ev.key.code == sf::Keyboard::S || 
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::Space 
				)
			) 
		{
			this->player->resetAnimationTimer();
		}
	}

	this->updatePlayer();
	this->updateChest();
	this->updateCollision();
	this->updateGUI();
	this->updateWinScreen();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderChest()
{
	this->chest->render(this->window);
}

void Game::renderBackground()
{
	this->window.draw(this->background);
}

void Game::renderGUI()
{
	this->window.draw(this->timer);
	this->window.draw(this->tips);
}

void Game::renderWinScreen()
{
	if (this->gameWin && this->timeatCompletion + 5 < this->completionTimer.getElapsedTime().asSeconds()) {
		this->window.draw(this->winScreen);
		this->window.draw(this->win);
		this->window.draw(this->winTimerDisplay);
	}
}

void Game::render()
{
	// Clearing the window
	this->window.clear();
	// Rendering the window objects
	this->renderBackground();
	this->renderChest();
	this->renderPlayer();
	this->renderGUI();
	this->renderWinScreen();

	// Displaying the rendered window
	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}
