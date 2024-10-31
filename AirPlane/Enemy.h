#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy {
public:
    Enemy();
    void update(float deltaTime);
    void render(RenderWindow& window);
    void reset(); // hàm đặt lại kẻ thù khi bị tiêu diệt
    FloatRect getGlobalBounds(); // hàm lấy vùng bao quanh kẻ thù
    Vector2f getPosition();
    void setActive(bool state);
   
    
private:
    static Texture texture; // texture chung cho tất cả kẻ thù
    Sprite sprite;
    float speed;
    bool active;
    
};