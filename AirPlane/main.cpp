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
    Sprite bksprite;
    bksprite.setTexture(background);
    Player player;
    Score score;
    vector<Enemy> enemies(3);//tạo 3 kẻ thù
    Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        player.update(deltaTime, enemies, score);
        for (auto& enemy : enemies) {
            enemy.update(deltaTime);
        }
        if (score.getScore() > 200) {
            score.reset(); // 200 đ thì reset lại
            // thêm tính năng như quay lại menu chính hay sao thì thêm ở đây 
        }
        window.clear();
        window.draw(bksprite);
        player.render(window);
        for (auto& enemy : enemies) {
            enemy.render(window);
        }
        score.render(window);
        window.display();
    }
}
