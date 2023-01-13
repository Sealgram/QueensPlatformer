#include "CompiledLibraries.h"
#include "LegendofJahed.h"




using namespace sf;
using namespace std;


//Private Functions



void LegendofJahed::initWindow()
{
	this->window.create(VideoMode(1920,1080), "Legend of Jahed", Style::Close | Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void LegendofJahed::initPlayer()
{
	this->Jahed = new Player();
}

//Constructor
LegendofJahed::LegendofJahed() 
{
	this->initWindow();
	this->initPlayer();
	this->bkgTexture1.loadFromFile("Textures/Assets/Street.png");
	this->bkg1.setTexture(this->bkgTexture1);

	this->bkgTexture2.loadFromFile("Textures/Assets/Street2.png");
	this->bkg2.setTexture(this->bkgTexture2);

	this->bkgTexture3.loadFromFile("Textures/Assets/Street3.png");
	this->bkg3.setTexture(this->bkgTexture3);

	this->bkgTexture4.loadFromFile("Textures/Assets/Street4.png");
	this->bkg4.setTexture(this->bkgTexture4);

	this->bkgTexture5.loadFromFile("Textures/Assets/douglas.png");
	this->bkg5.setTexture(this->bkgTexture5);
	
	this->bkgs = { bkg1, bkg2, bkg3, bkg4, bkg5 };

	this->bkgController = 0;

	xPos1 = 1450;
	xPos2 = 1550;
	yPos1 = 750;
	yPos2 = 850;

}
//Destructor
LegendofJahed::~LegendofJahed()
{
	delete this->Jahed;
}
//Accessors

const RenderWindow& LegendofJahed::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}

void LegendofJahed::updatePlayer()
{
	this->Jahed->update();
}

void LegendofJahed::update()
{
	//Polling Window Events
	while (this->window.pollEvent(this->ev)) {

		if (this->ev.type == Event::Closed)
			this->window.close();
		else if(this->ev.type == Event::KeyPressed && this->ev.key.code == Keyboard::Escape)
			this->window.close();
	}

	this->updatePlayer();

}

void LegendofJahed::renderPlayer()
{
	this->Jahed->render(this->window);
}

void LegendofJahed::render()
{

	this->window.clear(Color(255,255,255));

	//render game
	if (bkgController == 3) {



		cout << this->Jahed->getPosition().x << ", " << this->Jahed->getPosition().y << endl;
		if (((xPos1 <= this->Jahed->getPosition().x) && (this->Jahed->getPosition().x <= xPos2)) && ((yPos1 <= this->Jahed->getPosition().y) && (this->Jahed->getPosition().y <= yPos2))) {
			bkgController = 4;

		}


	}
	if (this->Jahed->getBkgController()) {

		bkgController += 1;



		if (bkgController > 3)
			bkgController = 0;

		this->Jahed->resetBkgController();
	}
	this->window.draw(this->bkgs.at(this->bkgController));
	this->renderPlayer();


	this->window.display();
}
