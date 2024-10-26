#include "Animation.h"




//Hiệu ứng nổ khi địch bị hạ
Explosion::Explosion(Vector2f position) {
    currentSprite = 0;
    active = true;
    time = 0;
    // Tải 6 hình ảnh nổ
    for (int i = 0; i < 6; ++i) {
        sf::Texture texture;
        if (texture.loadFromFile("../Data/Explosion" + to_string(i) + ".png")) {
            textures.push_back(texture);
        }
    }

    sprite.setPosition(position);
    sprite.setTexture(textures[0]);
}

void Explosion::render(RenderWindow& window, float deltatime) {
    time += deltatime;
    if (active) {
        sprite.setTexture(textures[currentSprite]); // Đặt texture tương ứng
        window.draw(sprite); // Vẽ hiệu ứng

        if (time > 100 * deltatime) {
            currentSprite++;
            time = 0;
        }
        if (currentSprite >= textures.size()) {
            active = false; // Ngừng hoạt động khi đã phát hết hình ảnh
        }
    }
}

bool Explosion::isActive() const {
    return active; // Trả về trạng thái hoạt động của hiệu ứng
}



// Phần mạng sống của nhân vật
Heart::Heart() {
    currentheart = 0;
    for (int i = 0; i < 5; i++) {
        Texture texture;
        if (texture.loadFromFile("../Data/heart_" + to_string(i) + ".png")) {
            textures.push_back(texture);
        }
    }
    sprite.setPosition(0, 0);
}
void Heart::Render(RenderWindow& window) {
    sprite.setTexture(textures[currentheart]);
    sprite.setScale(2, 2);
    window.draw(sprite);
}
bool Heart::Damaged() {
    currentheart++;
    if (currentheart > 4) {
        currentheart = 4;
        return false;
    }
    else return true;
}