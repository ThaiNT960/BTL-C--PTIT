#include "Player.h"

Player::Player() {
    if (!texture.loadFromFile("../Data/ship1.png")) {}
    sprite.setTexture(texture);
    sprite.setPosition(100, 300);
    speed = 800.0f;
    canShoot = true;
}

void Player::shoot()
{
    //Vị trí đạn bắn ra
    bullets.emplace_back(sprite.getPosition().x + sprite.getGlobalBounds().width,
        sprite.getPosition().y + sprite.getGlobalBounds().height / 2);
}

void Player::update(float deltaTime, vector<Enemy>& enemies, Score& score) {
    //Bắt phím di chuyển của người chơi
    if (Keyboard::isKeyPressed(Keyboard::W) && sprite.getPosition().y - speed * deltaTime > 0) {
        sprite.move(0, -speed * deltaTime);
    }
    if (Keyboard::isKeyPressed(Keyboard::S) && sprite.getPosition().y + sprite.getGlobalBounds().height + speed * deltaTime < 843) {
        sprite.move(0, speed * deltaTime);
    }
    if (Keyboard::isKeyPressed(Keyboard::D) && sprite.getPosition().x + sprite.getGlobalBounds().width + speed * deltaTime < 1500) {
        sprite.move(speed * deltaTime, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::A) && sprite.getPosition().x - speed * deltaTime > 0) {
        sprite.move(-speed * deltaTime, 0);
    }

    // Kiểm tra việc bắn đạn
    if (Keyboard::isKeyPressed(Keyboard::Space) && canShoot) {
        shoot();
        canShoot = false;
    }
    // Kiểm tra khi nào nhả phím Space
    if (!Keyboard::isKeyPressed(Keyboard::Space)) {
        canShoot = true; // Khi nhả phím,cho phép bắn đạn 
    }


    // Cập nhật vị trí các viên đạn and kiểm tra va chạm với kẻ thù
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update(deltaTime); // Goi hàm update trong bullet.h,deltaTime

        // kiểm tra va chạm giữa đạn và kẻ thù
        bool hit = false;
        for (auto& enemy : enemies) {
            if (it->getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                it = bullets.erase(it); // xóa đạn
                enemy.reset(); // đặt lại kẻ thù
                score.tăng(10); //tăng 10 điểm
                hit = true;
                break;
            }
        }
            if (!hit) {
            ++it; // nếu không có va chạm thì tiếp tục
        }
    }
}
void Player::render(RenderWindow& window) {
    window.draw(sprite);
    for (auto& bullet : bullets) {
        bullet.render(window);
    }
}
