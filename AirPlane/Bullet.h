#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet {
public:
    Bullet(float x, float y);
    void update(float deltaTime);
    void render(RenderWindow& window);
    FloatRect getGlobalBounds(); // hàm lấy vùng bao quanh đạn

private:
    Texture texture;
    Sprite sprite;
    float speed;
};
