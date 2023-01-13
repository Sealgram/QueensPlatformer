#include "stdafx.h"
#include "Game.h"

// Private functions
void Game::initWindow()
{
	// Initializing the window
	this->window.create(sf::VideoMode(1920,1080), "The Legend of Jahed", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}//1920,1080

void Game::initPlayer() {
	this->player = new Player();
}

// Constructors & Destructors
Game::Game() {
	this->initWindow();
	this->initPlayer();
	this->map.loadFromFile("Textures/Campus.png");
	this->background.setTexture(this->map);
	this->background.setScale(12.f,12.f);
	this->screenState = PLAYER_SCREEN_STATES::PLAY;
	this->clock.restart();
	this->iconAnim = -10.f;
	this->clockAnim.restart();
	this->spIcon.setPosition(450.f,220.f);
}

Game::~Game() {
	delete this->player;
}

// Public functions
void Game::updatePlayer() {
	this->player->update();
}

void Game::update() {
	// Polling window events
	while (this->window.pollEvent(this->ev)) {
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();
	}
	this->openMap();
	if(this->screenState == PLAY){
		this->updatePlayer();
	}
}

void Game::renderPlayer() {
	this->player->render(this->window);
}

void Game::render() {
	// Clearing the window
	this->window.clear();

	// Rendering the window objects
	if(this->screenState == PLAY){
		this->renderPlayer();
	}else{
		this->setUpMap();
	}
	// Displaying the rendered window
	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

void Game::openMap(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)){
		if(clock.getElapsedTime() > sf::seconds(0.2f)){
			if(this->screenState == PLAY){
				screenState = MAP;
			}else{
				screenState = PLAY;
			}
			this->clock.restart();
		}
	}
}

void Game::setUpMap(){
	sf::Sprite book;

	sf::Texture icon;
	sf::Sprite desk;
	icon.loadFromFile("Textures/desk.png");
	desk.setTexture(icon);
	desk.setScale(5.f,5.f);
	desk.setPosition(0.f,0.f);
	this->window.draw(desk);
	this->window.draw(this->background);
	icon.loadFromFile("Textures/pxArt.png");
	book.setTexture(icon);
	book.setPosition(800.f,0.f);
	this->window.draw(book);
	icon.loadFromFile("Textures/icon.png");
	this->spIcon.setTexture(icon);
	

	//Map animation
	if(this->clockAnim.getElapsedTime() > sf::seconds(0.55f)){
		this->spIcon.move(0.f,this->iconAnim);
		this->iconAnim *=-1;
		this->clockAnim.restart();
	}
	float y = spIcon.getPosition().y;
	this->window.draw(spIcon);

	//Set icon to legends position
	spIcon.setScale(3.f,3.f);
	spIcon.setPosition(880.f,190.f);
	this->window.draw(spIcon);

	//Set icon position to map
	spIcon.setPosition(450.f,y);
	spIcon.setScale(1.f,1.f);

	sf::Text text;
	sf::Font font;
	font.loadFromFile("Fonts/open-sans/OpenSans-Regular.ttf");
	text.setFont(font);
	text.setString("Douglas Library");
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(30);
	text.setPosition(970.f,210.f);
	//text.setPosition(910.f,200.f);
	this->window.draw(text);
;	//spIcon.setPosition(300.f,300.f);
	//this->window.draw(spIcon);
}
