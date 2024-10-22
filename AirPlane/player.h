#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"
#include "Enemy.h"
#include "Score.h"
using namespace std;
using namespace sf;

class Player {
public:
    Player();
    void update(float deltaTime, vector<Enemy>& enemies, Score& score);
    void render(RenderWindow& window);
    void shoot(); // Hàm bắn đạn

private:
    Texture texture;
    Sprite sprite;
    float speed;
    vector<Bullet> bullets; // Danh sách đạn bắn ra
    bool canShoot;
};
