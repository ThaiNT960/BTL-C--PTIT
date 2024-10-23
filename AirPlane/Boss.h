#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Boss {
public :
	Boss();
	void update(float deltaTime);
	void render(RenderWindow& window);
	bool BossDefeat();
	FloatRect getGlobalBounds();
	void decrease(int tmp);
private:
	Texture texture;
	Sprite sprite;
	float speed;
	int Health;
 };