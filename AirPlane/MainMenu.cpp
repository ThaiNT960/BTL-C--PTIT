#include "MainMenu.h"
#include <iostream>  

MainMenu::MainMenu(float width, float height) {
    if (!font.loadFromFile("../Data/PressStart2P-Regular.TTF")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Tải file âm thanh
    if (!soundBuffer.loadFromFile("../Data/Menu Selection Click.wav")) {
        std::cerr << "Error loading sound!" << std::endl;
    }
    sound.setBuffer(soundBuffer);
    if (!fightSoundBuffer.loadFromFile("../Data/fight-deep-voice-172194.wav")) {
        std::cerr << "Error loading fight sound!" << std::endl;
    }
    fightSound.setBuffer(fightSoundBuffer);
    
    // Tải nhạc nền
    if (!backgroundMusic.openFromFile("../Data/mrketid-127881.wav")) {
        std::cerr << "Error loading background music!" << std::endl;
    }
    backgroundMusic.setLoop(true);  // Lặp lại nhạc nền
    backgroundMusic.setVolume(95); // Điều chỉnh âm lượng nhạc nền nếu cần

    gameTitle.setFont(font);
    gameTitle.setString("Sky Warriors");
    gameTitle.setCharacterSize(80);  // Kích thước chữ lớn
    gameTitle.setFillColor(sf::Color::White);  // Màu chữ trắng
    gameTitle.setPosition(width / 2 - gameTitle.getGlobalBounds().width / 2, height / 6);  // Vị trí tên game


    std::string menuOptions[Max_main_menu] = { "Play", "Options", "About", "Exit" };
    for (int i = 0; i < Max_main_menu; i++) {
        mainMenu[i].setFont(font);
        mainMenu[i].setFillColor(sf::Color::White);
        mainMenu[i].setString(menuOptions[i]);
        mainMenu[i].setCharacterSize(60);
        mainMenu[i].setPosition(width / 2 - mainMenu[i].getGlobalBounds().width / 2, height / 3 + i * 100);  // Vị trí menu
    }

    MainMenuSelected = 0;
    mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
    background.setSize(sf::Vector2f(width, height));  
    background.setFillColor(sf::Color(0, 0, 0, 100)); 
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(gameTitle);
    for (int i = 0; i < Max_main_menu; ++i) {
        window.draw(mainMenu[i]);
    }
}

void MainMenu::MoveUp() {
    mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
    MainMenuSelected--;
    if (MainMenuSelected < 0)
        MainMenuSelected = Max_main_menu - 1;
    mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);

    // Phát âm thanh khi di chuyển lên
    sound.play();
}

void MainMenu::MoveDown() {
    mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
    MainMenuSelected++;
    if (MainMenuSelected >= Max_main_menu)
        MainMenuSelected = 0;
    mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);

    // Phát âm thanh khi di chuyển xuống
    sound.play();
}

int MainMenu::MainMenuPressed() {
    sound.play();
    if (MainMenuSelected == 0) {
        fightSound.play();  // Phát âm thanh fight khi chọn "Play"
        backgroundMusic.play();
    }
    return MainMenuSelected;
}
