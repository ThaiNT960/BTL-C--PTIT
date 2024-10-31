﻿#include "Boss.h"

Boss::Boss()
{
	if(!texture.loadFromFile("../Data/boss.png")){}
	sprite.setTexture(texture);
	sprite.setPosition(1500, 200);
	speed = 200.f;
	Health = 400;
	shootCooldown = 2.0f;    // Sau 2s lại bắn tiếp
	shootCooldownTimer = 0.f; 
	active = false;

	// Thiết lập thanh HP
	healthBar.setFillColor(Color::Blue);
	healthBar.setSize(Vector2f(Health*0.7f,10.f)); // Kích thước HP
	healthBar1.setFillColor(Color(100,100,100,150));
	healthBar1.setSize(Vector2f(280.f,10.f)); // Kích thước nền 
}

void Boss::update(float deltaTime)
{
	sprite.move(-speed * deltaTime, 0);
	if (sprite.getPosition().x < 500) {
		sprite.setPosition(500, sprite.getPosition().y);
		speed = -speed;
	}
	if (sprite.getPosition().x + sprite.getGlobalBounds().width >1500) {
		sprite.setPosition(1500-sprite.getGlobalBounds().width, sprite.getPosition().y);
		speed = -speed;
	}
	
	shootCooldownTimer += deltaTime;
	if (shootCooldownTimer >= shootCooldown) {
		shoot();
		shootCooldownTimer = 0.f; 
	}

	// Cập nhật vị trí của đạn
	for (auto& bullet : bullets) {
		bullet.update(deltaTime);
	}
	// Cập nhật thanh HP
	updateHealthBar();
}
bool Boss::BossDefeat()
{
	if (Health <= 0)  return true;
	return false;
}

FloatRect Boss::getGlobalBounds() {
	if (Health <= 0) return FloatRect(0,0,0,0);
	return sprite.getGlobalBounds(); 
}

void Boss::decrease(int tmp)
{
	Health -= tmp;
}

void Boss::shoot()
{
	float x = sprite.getPosition().x;
	float y = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;
	vector<Vector2f> direction = {
	{1.f, 0.f},   // Đạn thẳng 
	{1.f, -0.2f}, // Đạn chéo lên
	{1.f, 0.2f},  // Đạn chéo xuống
	{1.f, -0.5f}, // Đạn bắn góc lớn lên
	{1.f, 0.5f}   // Đạn bắn góc lớn xuống
	};
	for (auto& pos : direction) {
		BossBullet bullet(x,y);
		bullet.setDirection(pos);
		bullets.push_back(bullet);
	}
}
void Boss::setActive(bool state) {
	active = state;
}

bool Boss::isActive() {
	return active;
}
void Boss::render(RenderWindow& window)
{
	window.draw(sprite);
	for (auto& bullet : bullets) {
		bullet.render(window);
	}
	// Vẽ thanh máu
	window.draw(healthBar1);
	window.draw(healthBar);
}
void Boss::updateHealthBar()
{
	// Cập nhật kích thước thanh HP
	healthBar.setSize(Vector2f(Health*0.7f,10.f));
	// Đặt vị trí thanh HP
	healthBar.setPosition(sprite.getPosition().x,sprite.getPosition().y - 20.f);
	healthBar1.setPosition(sprite.getPosition().x,sprite.getPosition().y - 20.f);
}