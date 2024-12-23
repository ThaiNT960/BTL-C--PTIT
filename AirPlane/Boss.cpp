﻿#include "Boss.h"
#include <iostream>  

Boss::Boss() {
    if (!texture.loadFromFile("../Data/U-GANDAM Blue Model.png")) {
        std::cerr << "Error loading boss texture!" << std::endl;
    }
    if (!victorySoundBuffer.loadFromFile("../Data/victory-voiced-165989.wav")) {
        std::cerr << "Error loading victory sound!" << std::endl;
    }
    victorySound.setBuffer(victorySoundBuffer);
    sprite.setTexture(texture);
    sprite.setPosition(1500, 250);
    sprite.setScale(1.1f,1.1f);
    speed = 200.f;
    Health = 400;
    shootCooldown = 2.0f;    // Sau 2s lại bắn tiếp
    shootCooldownTimer = 0.f;
    active = false;
    victorySoundPlayed = false;

    // Tải âm thanh cảnh báo
    if (!alarmSoundBuffer.loadFromFile("../Data/ambient_alarm1.wav")) {
        std::cerr << "Error loading alarm sound!" << std::endl;
    }
    alarmSound.setBuffer(alarmSoundBuffer);
    alarmSound.setVolume(50.f);

    // Thiết lập thanh HP
    healthBar.setFillColor(Color::Blue);
    healthBar.setSize(Vector2f(Health * 0.5f, 10.f)); // Kích thước HP
    healthBar1.setFillColor(Color(100, 100, 100, 150));
    healthBar1.setSize(Vector2f(200.f, 10.f)); // Kích thước nền
}

void Boss::update(float deltaTime) {
    if (active && alarmPlayCount < 1) {
        if (alarmSound.getStatus() == Sound::Stopped) {
            alarmSound.play();
            alarmPlayCount++;
        }
    }
    sprite.move(-speed * deltaTime, 0);
    if (sprite.getPosition().x < 500) {
        sprite.setPosition(500, sprite.getPosition().y);
        speed = -speed;
    }
    if (sprite.getPosition().x + sprite.getGlobalBounds().width > 1500) {
        sprite.setPosition(1500 - sprite.getGlobalBounds().width, sprite.getPosition().y);
        speed = -speed;
    }

    shootCooldownTimer += deltaTime;
    if (shootCooldownTimer >= shootCooldown) {
        shoot();
        shootCooldownTimer = 0.f;
    }

    // Cập nhật vị trí của đạn
    for (auto& bullet : bullets) {
        bullet.update(deltaTime);
    }

    // Cập nhật thanh HP
    updateHealthBar();
}

bool Boss::BossDefeat() {
    if (Health <= 0) {
        if (!victorySoundPlayed) {  
            victorySound.play();
            victorySoundPlayed = true;  
        }
        return true;
    }
    return false;
}

FloatRect Boss::getGlobalBounds() {
    if (Health <= 0) return FloatRect(0, 0, 0, 0);
    return FloatRect(sprite.getPosition().x+52,sprite.getPosition().y, sprite.getGlobalBounds().height, sprite.getGlobalBounds().width);
}

void Boss::decrease(int damage) {
    Health -= damage;
}

void Boss::shoot() {
    float x = sprite.getPosition().x;
    float y = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;
    vector<Vector2f> direction = {
        {1.f, 0.f},   // Đạn thẳng 
        {1.f, -0.2f}, // Đạn chéo lên
        {1.f, 0.2f},  // Đạn chéo xuống
        {1.f, -0.5f}, // Đạn bắn góc lớn lên
        {1.f, 0.5f}   // Đạn bắn góc lớn xuống
    };
    for (auto& dir : direction) {
        BossBullet bullet(x, y);
        bullet.setDirection(dir);
        bullets.push_back(bullet);
    }
}

void Boss::setActive(bool state) {
    if (state && !active) {  // Nếu boss được kích hoạt lần đầu
        alarmPlayCount = 0;
        alarmSound.play();    // Phát âm thanh cảnh báo
    }
    active = state;
}

bool Boss::isActive() {
    return active;
}


void Boss::render(RenderWindow& window) {
    window.draw(sprite);
    for (auto& bullet : bullets) {
        bullet.render(window);
    }
    // Vẽ thanh máu
    window.draw(healthBar1);
    window.draw(healthBar);
}

void Boss::updateHealthBar() {
    // Cập nhật kích thước thanh HP
    healthBar.setSize(Vector2f(Health * 0.5f, 10.f));
    // Đặt vị trí thanh HP
    healthBar.setPosition(sprite.getPosition().x+35.f, sprite.getPosition().y - 20.f);
    healthBar1.setPosition(sprite.getPosition().x+35.f, sprite.getPosition().y - 20.f);
}

void Boss::Reset() {
    sprite.setPosition(1500, 200);
    speed = 200.f;
    Health = 400;
    shootCooldown = 2.0f;    // Sau 2s lại bắn tiếp
    shootCooldownTimer = 0.f;
    active = false;
    victorySoundPlayed = false;

    // Thiết lập thanh HP
    healthBar.setFillColor(Color::Blue);
    healthBar.setSize(Vector2f(Health * 0.5f, 10.f)); // Kích thước HP
    healthBar1.setFillColor(Color(100, 100, 100, 150));
    healthBar1.setSize(Vector2f(200.f, 10.f)); // Kích thước nền
}
bool Boss::Attack(FloatRect t) {
    bool hit = false;
    for (auto it = bullets.begin(); it != bullets.end();) {
        if (it->getGlobalBounds().intersects(t)) {
            it = bullets.erase(it);
            hit = true;
            break;
        }
        if (!hit)++it;
    }
    return hit;
}
Vector2f Boss::getPosition()
{
    return sprite.getPosition();
}