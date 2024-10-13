#pragma once
#include<SFML/Graphics.hpp>
#include <vector>
#include"Bullet.h"
using namespace std;
using namespace sf;
class Player {
	public:
		Player();   // ham khoi tao
		void update(); // ham cap nhat trang thai
		void render(RenderWindow& window);// ham vẽ máy bay
		void shoot(); // hàm bắn đạn
		
	private:
		Texture texture;
		Sprite sprite;
		float speed;
		vector<Bullet> bullets;// danh sách đạn bắn ra
		bool canShoot;
};