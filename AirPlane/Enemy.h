#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    void Reset();
    void playExplosionSound();
    
private:
    static Texture texture; // texture chung cho tất cả kẻ thù
    Sprite sprite;
    float speed;
    bool active;
    SoundBuffer explosionBuffer;  // Buffer âm thanh nổ
    Sound explosionSound;
};