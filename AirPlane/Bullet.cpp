#include "Bullet.h"

Bullet::Bullet(float x ,float y)
{
	if (!texture.loadFromFile("../Data/laser.png")) {
	}
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	speed = 1.0f;

}


void Bullet::update()
{
	sprite.move(speed, 0);
}

void Bullet::render(RenderWindow& window)
{
	   window.draw(sprite);
}


