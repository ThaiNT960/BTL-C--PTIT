#include "Boss.h"

Boss::Boss()
{
	if(!texture.loadFromFile("../Data/boss.png")){}
	sprite.setTexture(texture);
	sprite.setPosition(1500, 200);
	speed = 200.f;
	Health = 500;
}

void Boss::update(float deltaTime)
{
	sprite.move(speed * deltaTime, 0);
	if (sprite.getPosition().x < 500) {
		sprite.setPosition(500, sprite.getPosition().y);
		speed = -speed;
	}
	if (sprite.getPosition().x + sprite.getGlobalBounds().width >1500) {
		sprite.setPosition(1500-sprite.getGlobalBounds().width, sprite.getPosition().y);
		speed = -speed;
	}

}

void Boss::render(RenderWindow& window)
{
	window.draw(sprite);
}

bool Boss::BossDefeat()
{
	if (Health <= 0)  return true;
	return false;
}

FloatRect Boss::getGlobalBounds() {
	
	return sprite.getGlobalBounds(); 
}

void Boss::decrease(int tmp)
{
	Health -= tmp;
}
