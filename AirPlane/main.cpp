#include "player.h";

int main()
{
	RenderWindow window(VideoMode(800, 600), "AirPlane");
	Texture background;
	if (!background.loadFromFile("../Data/bkground.png")) {
		return -1;
	}
	Sprite bksprite;
	bksprite.setTexture(background);
	
	Player player;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		player.update();
		window.draw(bksprite);
		player.render(window);
		window.display();
	}
}