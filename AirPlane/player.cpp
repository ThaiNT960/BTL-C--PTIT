#include "Player.h"

Player::Player() {
    if (!texture0.loadFromFile("../Data/ship1.png")) {};
    if (!texture1.loadFromFile("../Data/ship2.png")) {};
    if (!shootBuffer.loadFromFile("../Data/soundshoot.ogg")) {};
    if (!collisionBuffer.loadFromFile("../Data/break-boom-fx-240235.wav")) {};
    sprite.setTexture(texture0);
    shootSound.setBuffer(shootBuffer);
    collisionSound.setBuffer(collisionBuffer);
    sprite.setPosition(100, 300);
    speed = 600.0f;
    canShoot = true;
    activity = true;
    clock = 0;
    shootClock = 0;
    damaged = false;
    bullet.setPosition(sprite.getPosition());
}

void Player::shoot() {
    bullets.push_back(bullet);
}
FloatRect Player::getGlobalBounds() { return sprite.getGlobalBounds();}


void Player::update(float deltaTime, vector<Enemy>& enemies, Score& score, Boss& boss) {
    //Bắt phím di chuyển của người chơi
    if (Keyboard::isKeyPressed(Keyboard::W) && sprite.getPosition().y - speed * deltaTime > 0) sprite.move(0, -speed * deltaTime);
    else if (Keyboard::isKeyPressed(Keyboard::S) && sprite.getPosition().y + sprite.getGlobalBounds().height + speed * deltaTime < 843) sprite.move(0, speed * deltaTime);
    else if (Keyboard::isKeyPressed(Keyboard::D) && sprite.getPosition().x + sprite.getGlobalBounds().width + speed * deltaTime < 1500) sprite.move(speed * deltaTime, 0);
    else if (Keyboard::isKeyPressed(Keyboard::A) && sprite.getPosition().x - speed * deltaTime > 0) sprite.move(-speed * deltaTime, 0);
    bullet.setPosition(sprite.getPosition());
 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootClock > 0.2f) {
        shoot();
        shootSound.play();
        shootClock = 0;
    }
    else shootClock += deltaTime;
    // Cập nhật vị trí các viên đạn and kiểm tra va chạm với kẻ thù
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->update(deltaTime); // Goi hàm update trong bullet.h,deltaTime
        // kiểm tra va chạm giữa đạn và enemy
        bool hit = false;
        for (auto& enemy : enemies) {
            
            if (it->getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                it = bullets.erase(it); // xóa đạn
                enemy.playExplosionSound();
                Explosion t(enemy.getPosition());
                explosions.emplace_back(t);
                enemy.reset(); // đặt lại kẻ thù
                score.tăng(10); //tăng 10 điểm
                if (score.getScore() >= 200) activity = false;
                hit = true;
                break;
            }
        }
        if (!hit) it++;
    }
    //Kiểm tra va chạm giữa player vs enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
        if (damaged) break;
        bool hit = false;
        if (it->getGlobalBounds().intersects(sprite.getGlobalBounds())) {
            Damaged(deltaTime);
            Explosion t(it->getPosition());
            explosions.emplace_back(t);
            it->reset();
            collisionSound.play();
            it->playExplosionSound();
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
    //Kiểm tra va chạm giữa player và bossbullet
    if (!damaged&&boss.isActive()) {
        bool sum = boss.Attack(getGlobalBounds());
        if (sum) {
            Damaged(deltaTime);
            collisionSound.play();
        } 
    }
    //Ktra va chạm giữa player và boss;
    if (boss.isActive() && !damaged && getGlobalBounds().intersects(boss.getGlobalBounds())) {
        Damaged(deltaTime);
        collisionSound.play();
    }
    
}

void Player::render(RenderWindow& window, float deltatime) {
    Blink(deltatime);
    window.draw(sprite);
    heart.Render(window);
    
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].getPosition().x > 1500) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
        else bullets[i].render(window);
    }
    for (int i = 0; i < explosions.size(); i++) {
        if (!explosions[i].isActive()) {
            explosions.erase(explosions.begin() + i);
            i--;
        }
        else  explosions[i].render(window, deltatime);
       
    }

}
bool Player::Activity() {
    return activity;
}
void Player::Damaged(float t) {
    activity = heart.Damaged();
    clock = 3000*t;
    damaged = true;
}
void Player::Blink(float t) {
    if (clock >= 3000*t ) sprite.setTexture(texture1);
    else if (clock >= 2000*t ) sprite.setTexture(texture0);
    else if (clock >= 1000*t ) sprite.setTexture(texture1);
    else sprite.setTexture(texture0);
    clock -=t;
    if (clock < 0) {
        clock = 0;
        damaged = false;
    }
}
void Player::Reset() {
    sprite.setPosition(100, 300);
    speed = 600.0f;
    activity = true;
    clock = 0;
    shootClock = 0;
    damaged = false;
    bullet.setPosition(sprite.getPosition());
    heart.Reset();
    explosions.clear();
}
Vector2f Player::getPosition() {
    return sprite.getPosition();
}