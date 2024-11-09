#pragma once
#include "BossBullet.h"
#include<SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;
class Boss {
public :
	Boss();
	void update(float deltaTime);
	void render(RenderWindow& window);
	bool BossDefeat();
	FloatRect getGlobalBounds();
	void decrease(int tmp);
	void shoot();
	void setActive(bool state); 
	bool isActive(); 
	void Reset();
private:
	Texture texture;
	Sprite sprite;
	float speed;
	int Health;
	vector<BossBullet> bullets;  
	float shootCooldown ;     // Thời gian giữa hai lần bắn liên tiếp 
	float shootCooldownTimer ; // Khởi tạo bộ đếm thời gian
	bool active;
	RectangleShape healthBar;      // Thanh HP
	RectangleShape healthBar1;  // Thanh nền
	void updateHealthBar(); // Cập nhật thanh HP 
 };