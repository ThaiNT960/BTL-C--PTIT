#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class BossBullet {
public:
	BossBullet(float x, float y);
	void update(float deltaTime);
	void render(RenderWindow& window);
	FloatRect getGlobalBounds();
	void setDirection(Vector2f dir);
private:
	Texture texture;
	Sprite sprite;
	float speed;
	Vector2f direction;
};