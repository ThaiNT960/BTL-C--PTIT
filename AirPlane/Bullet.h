#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet {
public:
    Bullet();
    void update(float deltaTime);
    void render(RenderWindow& window);
    FloatRect getGlobalBounds(); // hàm lấy vùng bao quanh đạn
    Vector2f getPosition();
    void setPosition(Vector2f);
private:
    Texture texture;
    Sprite sprite;
    float speed;
  
};
