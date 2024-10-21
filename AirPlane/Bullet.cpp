#include "Bullet.h"

Bullet::Bullet(float x, float y) {
    if (!texture.loadFromFile("../Data/laser.png")) {}
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    speed = 900.f;
}

void Bullet::update(float deltaTime) {
    sprite.move(speed * deltaTime, 0);
}

void Bullet::render(RenderWindow& window) {
    window.draw(sprite);
}
FloatRect Bullet::getGlobalBounds() {
    return sprite.getGlobalBounds(); // trả về vùng bao quanh đạn
}
