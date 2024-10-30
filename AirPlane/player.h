#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"
#include "Enemy.h"
#include "Score.h"
#include "Boss.h"
#include "Animation.h"
using namespace std;
using namespace sf;

class Player {
public:
    Player();
    void update(float deltaTime, vector<Enemy>& enemies, Score& score, Boss& boss);
    void render(RenderWindow& window, float dentatime);
    void shoot(); // Hàm bắn đạn
    FloatRect getGlobalBounds();
    bool Activity();
    void Damaged(float t);
    void Blink(float t);
private:
    Texture texture0;
    Texture texture1;//ảnh phụ
    Sprite sprite;
    float speed;
    vector<Bullet> bullets;// Danh sách đạn bắn ra
    vector<Explosion> explosions;
    bool canShoot;
    bool activity;
    Heart heart;
    float clock,clock1;
    bool damaged;
    Bullet bullet;
};