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
FloatRect Player::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

void Player::update(float deltaTime, vector<Enemy>& enemies, Score& score, Boss& boss) {
    //Bắt phím di chuyển của người chơi
    if (Keyboard::isKeyPressed(Keyboard::W) && sprite.getPosition().y - speed * deltaTime > 0) {
        sprite.move(0, -speed * deltaTime);
    }
    else if (Keyboard::isKeyPressed(Keyboard::S) && sprite.getPosition().y + sprite.getGlobalBounds().height + speed * deltaTime < 843) {
        sprite.move(0, speed * deltaTime);
    }
    else if (Keyboard::isKeyPressed(Keyboard::D) && sprite.getPosition().x + sprite.getGlobalBounds().width + speed * deltaTime < 1500) {
        sprite.move(speed * deltaTime, 0);
    }
    else if (Keyboard::isKeyPressed(Keyboard::A) && sprite.getPosition().x - speed * deltaTime > 0) {
        sprite.move(-speed * deltaTime, 0);
    }

    // Kiểm tra việc bắn đạn
    if (Keyboard::isKeyPressed(Keyboard::Space) && canShoot) {
        shoot();
        canShoot = false;
    }
    if (!Keyboard::isKeyPressed(Keyboard::Space)) {
        canShoot = true; // Khi nhả phím,cho phép bắn đạn 
    }



    // Cập nhật vị trí các viên đạn and kiểm tra va chạm với kẻ thù
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update(deltaTime); // Goi hàm update trong bullet.h,deltaTime

        // kiểm tra va chạm giữa đạn và enemy
        bool hit = false;
        for (auto& enemy : enemies) {
            if (it->getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                it = bullets.erase(it); // xóa đạn
                Explosion t(enemy.getPosition());
                explosions.emplace_back(t);
                enemy.reset(); // đặt lại kẻ thù
                score.tăng(10); //tăng 10 điểm
            //    if (score.getScore() >= 200) activity = false;
                hit = true;
                break;
            }
        }

        if (!hit) {
            ++it; // nếu không có va chạm thì tiếp tục
        }
    }
    //Kiểm tra va chạm giữa player vs enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
        bool hit = false;
        if (it->getGlobalBounds().intersects(sprite.getGlobalBounds())) {
            activity = false;
            break;
        }
        if (!hit) it++;
    }
    //Kiểm tra va chạm giữa đạn và Boss
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update(deltaTime);
        bool hit = false;
        if (it->getGlobalBounds().intersects(boss.getGlobalBounds())) {
            it = bullets.erase(it);
            boss.decrease(10);
            hit = true;
        }
        if (!hit)++it;
    }
    //Kiểm tra va chạm giữa player vs enemies
    if (boss.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
            activity = false;
           }
       
}

void Player::render(RenderWindow& window, float deltatime) {
    window.draw(sprite);
    for (auto& bullet : bullets) {
        bullet.render(window);
    }
    for (int i = 0; i < explosions.size(); i++) {
        explosions[i].render(window, deltatime);
    }

}
bool Player::Activity() {
    return activity;
}