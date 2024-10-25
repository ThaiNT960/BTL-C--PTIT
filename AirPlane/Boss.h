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
private:
	Texture texture;
	Sprite sprite;
	float speed;
	int Health;
	vector<BossBullet> bullets;  
	float shootCooldown ;     // Thời gian giữa hai lần bắn liên tiếp 
	float shootCooldownTimer ; // Khởi tạo bộ đếm thời gian
 };