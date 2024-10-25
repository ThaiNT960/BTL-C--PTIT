#include "Enemy.h"

Texture Enemy::texture;
Enemy::Enemy() {
    if (!texture.loadFromFile("../Data/enemy2.png")) {}
    sprite.setTexture(texture);

    // random y từ 0 đến 750 
    float randomY = rand() % 750;
    sprite.setPosition(1500, randomY);
    speed = 300.0f;
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
    return sprite.getGlobalBounds(); // trả về vùng bao quanh của kẻ thù
}
Vector2f Enemy::getPosition() {
    return sprite.getPosition();
}