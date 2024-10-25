#include "Explosion.h"

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

        if (time > 300 * deltatime) {
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