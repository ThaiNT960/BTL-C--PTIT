#include "Bullet.h"

Bullet::Bullet() {
    if (!texture.loadFromFile("../Data/14.png")) {}
    sprite.setTexture(texture);
    sprite.setScale(0.3, 0.3);
    sprite.setPosition(0,0);
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
Vector2f Bullet::getPosition() {
    return sprite.getPosition();
}
void Bullet::setPosition(Vector2f t) {
    sprite.setPosition(t.x+60,t.y+35);
}


