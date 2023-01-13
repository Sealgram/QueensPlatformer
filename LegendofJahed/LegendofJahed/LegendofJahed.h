#include "CompiledLibraries.h"
#include "Player.h"
#pragma once



using namespace std;
using namespace sf;


class LegendofJahed
{

private:
	//Variables
	RenderWindow window;
	Event ev;

	Player* Jahed;

	Texture bkgTexture1;
	Sprite bkg1;
	Texture bkgTexture2;
	Sprite bkg2;
	Texture bkgTexture3;
	Sprite bkg3;
	Texture bkgTexture4;
	Sprite bkg4;
	Texture bkgTexture5;
	Sprite bkg5;

	vector<Sprite> bkgs;

	int bkgController;






	void initWindow();
	void initPlayer();


public:

	//Constructors
	LegendofJahed();
	//Destructors
	virtual ~LegendofJahed();
	//Accessors

	//Function
	const RenderWindow& getWindow() const;
	void updatePlayer();
	void update();
	void renderPlayer();
	void render();

	float xPos1;
	float xPos2;
	float yPos1;
	float yPos2;
};

