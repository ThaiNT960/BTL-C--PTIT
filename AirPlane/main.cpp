#include <SFML/Graphics.hpp>
#include "ParallexBackground.h"
#include "Player.h"
#include "Enemy.h"
#include "Score.h"
#include "Boss.h"
#include "MainMenu.h" 

int main() {
    sf::RenderWindow window(sf::VideoMode(1500, 843), "AirPlane");

    // Tạo menu chính
    MainMenu mainMenu(1500, 843);

    // Tạo nền tối
    sf::RectangleShape darkOverlay(sf::Vector2f(1500, 843));
    darkOverlay.setFillColor(sf::Color(0, 0, 0, 150)); // Màu đen với độ mờ 150

    // Khởi tạo nền cuộn nhiều lớp
    ParallexBackground parallexBackground;
    parallexBackground.Init();

    // Tạo đối tượng trong trò chơi
    Player player;
    Score score;
    Boss boss;
    bool bossActive = false;
    std::vector<Enemy> enemies(3); // Tạo 3 kẻ thù
    sf::Clock clock;
    bool inMenu = true;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Xử lý menu
            if (inMenu) {
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::W) {
                        mainMenu.MoveUp();
                    }
                    if (event.key.code == sf::Keyboard::S) {
                        mainMenu.MoveDown();
                    }
                    if (event.key.code == sf::Keyboard::Space) {
                        int selection = mainMenu.MainMenuPressed();
                        switch (selection) {
                        case 0: // Bắt đầu trò chơi
                            inMenu = false;
                            break;
                        case 1:
                            // Xử lý options ở đây
                            break;
                        case 2:
                            // Xử lý about ở đây
                            break;
                        case 3: // Thoát
                            window.close();
                            break;
                        }
                    }
                }
            }
        }

        // Nếu không còn ở trong menu, tiếp tục với trò chơi
        if (!inMenu) {
            parallexBackground.Update(deltaTime); // Cập nhật nền cuộn nhiều lớp

            if (player.Activity()) {
                player.update(deltaTime, enemies, score, boss);
                if (score.getScore() >= 100 && !bossActive) {
                    bossActive = true;
                }
                if (bossActive) {
                    boss.update(deltaTime);
                    if (boss.BossDefeat()) {
                        bossActive = false;
                    }
                }
                else {
                    for (auto& enemy : enemies) {
                        enemy.update(deltaTime);
                    }
                }
            }

            // Vẽ màn hình
            window.clear();
            parallexBackground.Render(&window); // Vẽ nền cuộn nhiều lớp
            player.render(window, deltaTime);
            score.render(window);
            if (bossActive) {
                boss.render(window);
            }
            else {
                for (auto& enemy : enemies) {
                    enemy.render(window);
                }
            }

            // Hiển thị khi Win hoặc Lose
            if (boss.BossDefeat()) { // Win
                window.draw(darkOverlay);
            }
            else if (!player.Activity()) { // Lose
                window.draw(darkOverlay);
            }
        }
        else { // Nếu trong menu
            window.clear();
            parallexBackground.Render(&window); // Vẽ nền trong menu
            mainMenu.draw(window); // Vẽ menu
        }

        window.display();
    }

    return 0;
}
