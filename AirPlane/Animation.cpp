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
    if (explosionSoundBuffer.loadFromFile("../Data/large-realistic-explosion-08-190269.wav")) {
        explosionSound.setBuffer(explosionSoundBuffer);
    }
    if (!gameOverSoundBuffer.loadFromFile("../Data/game-over-deep-male-voice-gfx-sounds-1-00-03.wav")) {}
        gameOverSound.setBuffer(gameOverSoundBuffer);
        gameOverSound.setVolume(100.f);
    
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
        if (explosionSound.getStatus() != Sound::Playing) {
            explosionSound.play();
        }
        if (gameOverSound.getStatus() != sf::Sound::Playing) {
            gameOverSound.play();
        }
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
// Hiệu ứng khi thua
Lose::Lose() {
    currenttexture = 0;
    clock = 0;
    for (int i = 0; i < 63; ++i) {
        if (textures[i].loadFromFile("../Data/lose/img-" + to_string(i+2) + ".png")) {}
    }
    if (!gameOverSoundBuffer.loadFromFile("../Data/game-over-deep-male-voice-gfx-sounds-1-00-03.wav")) {};
    gameOverSound.setBuffer(gameOverSoundBuffer);
    gameOverSound.setVolume(100.f);
}
void Lose::render(Vector2f position, RenderWindow& window, float deltatime) {
    sprite.setPosition(position.x-180,position.y-160);
    sprite.setTexture(textures[currenttexture]);
    sprite.setScale(0.8f, 0.8f);
    window.draw(sprite);
    clock += deltatime;
    if (clock > 0.05f) {
        clock = 0;
        currenttexture++;
    }
    if (currenttexture == 1 && gameOverSound.getStatus() != Sound::Playing) {
        gameOverSound.play();  // Phát âm thanh game over khi bắt đầu hiệu ứng thua
    }
}
bool Lose::isActive() {
    if (currenttexture < 63) return true;
    else return false;
}
void Lose::Reset() {
    currenttexture = 0;
    clock = 0;
}

// Hiệu ứng khi thắng
Victory::Victory(Vector2f position) {
    active = true;

    // Tải ảnh chiến thắng
    if (!victoryTexture.loadFromFile("../Data/images.png")) {
       
    }
    victorySprite.setTexture(victoryTexture);
    victorySprite.setPosition(position.x+50, position.y -100); // Đặt ảnh dưới chữ "VICTORY!"

    // Tải font chữ "VICTORY!"
    if (!victoryFont.loadFromFile("../Data/PressStart2P-Regular.TTF")) {
       
    }

    // Thiết lập chữ "VICTORY!"
    victoryText.setFont(victoryFont);
    victoryText.setString("VICTORY!");
    victoryText.setCharacterSize(100); // Kích thước chữ
    victoryText.setFillColor(sf::Color::Yellow); // Màu chữ
    victoryText.setPosition(position.x-220, position.y-300); // Vị trí chữ "VICTORY!"
}

void Victory::render(RenderWindow& window) {
    if (active) {
        window.draw(victoryText);   // Vẽ chữ "VICTORY!"
        window.draw(victorySprite); // Vẽ ảnh chiến thắng
    }
}

void Victory::activate() {
    active = true;
}

void Victory::deactivate() {
    active = false;
}

bool Victory::isActive() const {
    return active;
}

Win::Win() {
    currenttexture = 0;
    clock = 0;
    for (int i = 0; i < 63; ++i) {
        if (textures[i].loadFromFile("../Data/win/tile0" + to_string(i + 1) + ".png")) {}
    }
    if (!gameWinSoundBuffer.loadFromFile("../Data/large-realistic-explosion-08-190269.wav")) {};
    gameWinSound.setBuffer(gameWinSoundBuffer);
    gameWinSound.setVolume(100.f);
}

void Win::render(Vector2f position, RenderWindow& window, float deltatime) {
    sprite.setPosition(position.x - 390, position.y - 285);
    sprite.setTexture(textures[currenttexture]);
    sprite.setScale(3.5f, 3.5f);
    window.draw(sprite);
    clock += deltatime;
    if (clock > 0.05f) {
        clock = 0;
        currenttexture++;
    }
    if (currenttexture == 1 && gameWinSound.getStatus() != Sound::Playing) {
        gameWinSound.play();  // Phát âm thanh game over khi bắt đầu hiệu ứng thắng
    }
}

bool Win::isActive() {
    if (currenttexture < 63) return true;
    else return false;
}

void Win::Reset() {
    currenttexture = 0;
    clock = 0;
}