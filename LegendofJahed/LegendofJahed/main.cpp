#include "CompiledLibraries.h"
#include "LegendofJahed.h"


using namespace std;
using namespace sf;

int main()
{
	srand(static_cast<unsigned>(time(0)));

	LegendofJahed game;


	while (game.getWindow().isOpen()) {
		game.update();
		game.render();
		
	}
	return 0;
}