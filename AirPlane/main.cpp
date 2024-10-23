#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "Score.h"

int main() {
    RenderWindow window(VideoMode(1500, 843), "AirPlane");
    Texture background;
    if (!background.loadFromFile("../Data/Clouds 1.png")) {
        return -1;
    }
    //Tạo nền tối
    sf::RectangleShape darkOverlay(sf::Vector2f(1500, 843));
    darkOverlay.setFillColor(sf::Color(0, 0, 0, 150)); // Màu đen với độ mờ 150
    darkOverlay.setPosition(0, 0);
    //Tọa nền
    Sprite bksprite;
    bksprite.setTexture(background);
    //Tạo đối tượng
    Player player;
    Score score;
    Boss boss;
    bool BossActive = false;
    vector<Enemy> enemies(3);//tạo 3 kẻ thù
    Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        if (player.Activity()) {
            player.update(deltaTime, enemies, score, boss);
            if (score.getScore() > 100 && !BossActive)BossActive = true;
            if (BossActive) {
                boss.update(deltaTime);
                if (boss.BossDefeat()) {
                    BossActive = false;
                    score.reset();
                }
            }
            else for (auto& enemy : enemies) enemy.update(deltaTime);
        }
        window.clear();
        window.draw(bksprite);
        player.render(window);
        score.render(window);
        if (BossActive) {
            boss.render(window);
        }
        else for (auto& enemy : enemies) enemy.render(window);
        //Hiển thị khi Win hoặc Lose
        if (score.getScore() >= 200) {//Win
            window.draw(darkOverlay);

        }
        else if (!player.Activity()) { //Lose
            window.draw(darkOverlay);
        }
        //Biểu diễn nó lên màn hình

        window.display();
    }
}
//hello ae