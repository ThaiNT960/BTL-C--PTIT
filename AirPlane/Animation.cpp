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
    currentheart = 3;
    for (int i = 0; i < 2; i++) {
        Texture texture;
        if (texture.loadFromFile("../Data/health" + to_string(i) + ".png")) {
            textures.push_back(texture);
        }
    }
    for (int i = 0; i < 3; i++) {
        Sprite sprite;
        sprite.setScale(0.09f,0.09f);
        sprite.setPosition(50*i, 10);
        sprite.setTexture(textures[0]);
        sprites.push_back(sprite);
    }
    
}
void Heart::Render(RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        window.draw(sprites[i]);
     }
}
bool Heart::Damaged() {
    currentheart--;
    sprites[currentheart].setTexture(textures[1]);
    if (currentheart ==0) {
        currentheart = 0;
        return false;
    }
    else return true;
}
void Heart::Reset() {
    for (int i = 0; i < 3; i++) {
        sprites[i].setTexture(textures[0]);
    }
    currentheart = 3;
}