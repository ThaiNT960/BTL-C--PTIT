#include <SFML/Graphics.hpp>
#include "ParallexBackground.h"
#include "Player.h"
#include "Enemy.h"
#include "Score.h"
#include "Boss.h"
#include "MainMenu.h" 

int main() {
    RenderWindow window(VideoMode(1500, 843), "AirPlane");

    // Tạo menu chính
    MainMenu mainMenu(1500, 843);
    //Tạo phím chuyển tiếp
    Font font;
    if (!font.loadFromFile("../Data/PressStart2P-Regular.TTF")) {};
    Text Next;
    Next.setCharacterSize(15);
    Next.setString("Click enter to continue");
    Next.setPosition(600, 680);
    Next.setFillColor(Color::White);
    Next.setFont(font);
    // Tạo nền tối
    RectangleShape darkOverlay(Vector2f(1500, 843));
    darkOverlay.setFillColor(Color(0, 0, 0, 150)); // Màu đen với độ mờ 150

    // Khởi tạo nền cuộn nhiều lớp
    ParallexBackground parallexBackground;
    parallexBackground.Init();

    // Tạo đối tượng trong trò chơi
    Player player;
    Score score;
    Boss boss;
    bool bossActive = false;
    vector<Enemy> enemies(3); // Tạo 3 kẻ thù
    Clock clock;
    bool inMenu = true;
    //Tạo hiệu ứng khi thắng và thua
    Lose animationlose;
    //
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Xử lý menu
            if (inMenu) {
                if (event.type == Event::KeyReleased) {
                    if (event.key.code ==Keyboard::W) {
                        mainMenu.MoveUp();
                    }
                    if (event.key.code == Keyboard::S) {
                        mainMenu.MoveDown();
                    }
                    if (event.key.code == Keyboard::Space) {
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

            if (player.Activity() && !boss.BossDefeat()) {
                player.update(deltaTime, enemies, score, boss);
                if (score.getScore() >= 100 && !boss.isActive()) {
                    boss.setActive(true) ;
                    for (auto& enemy : enemies) {
                        enemy.setActive(false);
                    }
                }
                if (boss.isActive()) {
                    boss.update(deltaTime);
                    if (boss.BossDefeat()) {
                        boss.setActive(false); 
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
            if(player.Activity())player.render(window, deltaTime);
            score.render(window);
            if (boss.isActive()) {
                boss.render(window); 
            }
            else if(!boss.BossDefeat()){
                for (auto& enemy : enemies) {
                    enemy.render(window);
                }
            }

            // Hiển thị khi Win hoặc Lose
            if (boss.BossDefeat()) {// Win

                window.draw(darkOverlay);
                window.draw(Next);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    inMenu = true;
                    player.Reset();
                    boss.Reset();
                    score.Reset();
                    for (int i = 0; i < 3; i++)enemies[i].Reset();

                }
            }
            else if (!player.Activity()) { // Lose
                if (animationlose.isActive()) {
                    animationlose.render(player.getPosition(), window, deltaTime);
                }
                else {
                    window.draw(darkOverlay);
                    window.draw(Next);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        inMenu = true;
                        player.Reset();
                        boss.Reset();
                        score.Reset();
                        for (int i = 0; i < 3; i++)enemies[i].Reset();
                        animationlose.Reset();
                    }
                }
                
            }
            //
        }
        else { // Nếu trong menu
            window.clear();
            parallexBackground.Render(&window); // Vẽ nền trong menu
            mainMenu.draw(window); // Vẽ menu
        }

        window.display();
    }

}
