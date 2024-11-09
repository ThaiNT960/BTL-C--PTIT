#include "Enemy.h"

Texture Enemy::texture;
Enemy::Enemy() {
    if (!texture.loadFromFile("../Data/enemy2.png")) {}
    sprite.setTexture(texture);
    if (!explosionBuffer.loadFromFile("../Data/explosion-detonation-94515.wav")) {}
    explosionSound.setBuffer(explosionBuffer);

    // random y từ 0 đến 750 
    float randomY = rand() % 750;
    sprite.setPosition(1500, randomY);
    speed = 300.0f;
    active = true;
}
void Enemy::reset() {
    // Đặt lại vị trí kẻ thù khi bị tiêu diệt or ra khỏi màn hình
    float randomY = rand() % 750;
    sprite.setPosition(1500, randomY); // xuất hiện lại bên phải màn hình
}
void Enemy::update(float deltaTime) {

    sprite.move(-speed * deltaTime, 0);

    // nếu kẻ thù ra khỏi màn hình, đặt lại vị trí
    if (sprite.getPosition().x + sprite.getGlobalBounds().width < 0) {
        reset();
    }
}
void Enemy::render(RenderWindow& window) {
    window.draw(sprite);
}
FloatRect Enemy::getGlobalBounds() {
    if (active)  return sprite.getGlobalBounds();
      return  FloatRect(0,0,0,0);
}
Vector2f Enemy::getPosition() {
    return sprite.getPosition();
}
void Enemy::setActive(bool state) {
    active = state; 
}
void Enemy::Reset() {
    active = true;
    float randomY = rand() % 750;
    sprite.setPosition(1500, randomY);
}
void Enemy::playExplosionSound() {
    explosionSound.play();  // Phát âm thanh nổ
}
