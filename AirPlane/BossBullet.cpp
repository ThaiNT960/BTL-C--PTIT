#include "BossBullet.h"

Texture BossBullet::texture;

BossBullet::BossBullet(float x, float y) {
    if (!texture.loadFromFile("../Data/Ebeam.png")) {}
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    speed = 900.f;
    direction = { 1.f, 0.f };
}

void BossBullet::update(float deltaTime) {
    sprite.move(direction.x * -speed * deltaTime, direction.y * speed * deltaTime);
}

void BossBullet::render(RenderWindow& window) {
    window.draw(sprite);
}

FloatRect BossBullet::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

void BossBullet::setDirection(Vector2f dir) {
    direction = dir;
}