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
    Boss boss;
    bool BossActive=false;
    vector<Enemy> enemies(3);//tạo 3 kẻ thù
    Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        player.update(deltaTime, enemies, score,boss);
      
        if (score.getScore() > 100 && !BossActive) {
            BossActive = true;

        }
        if (BossActive) {
            boss.update(deltaTime);
            if (boss.BossDefeat()) {
                BossActive = false;
                score.reset();
            }
        }
        else{
            for (auto& enemy : enemies) {
                enemy.update(deltaTime);
            }
        }
       
           
        



        window.clear();
        window.draw(bksprite);
        player.render(window);

       
        if (BossActive) {
            boss.render(window);
        }
        else {
            for (auto& enemy : enemies) {
                enemy.render(window);
            }
        }
        score.render(window);
        window.display();
    }
}
