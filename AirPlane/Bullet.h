#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Bullet {
public:
	Bullet (float x,float y);   // ham khoi tao
	void update(); // ham cap nhat trang thai
	void render(RenderWindow& window);// ham vẽ 


private:
	Texture texture;
	Sprite sprite;
	float speed;
};
