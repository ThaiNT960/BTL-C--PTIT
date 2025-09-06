#include "MainMenu.h"
#include <iostream>  
#include <array>


MainMenu::MainMenu(float width, float height) {
    if (!font.loadFromFile("../Data/PressStart2P-Regular.TTF")) {
        cerr << "Error loading font!" << endl;
    }

    // Tải file âm thanh
    if (!soundBuffer.loadFromFile("../Data/Menu Selection Click.wav")) {
        cerr << "Error loading sound!" << endl;
    }
    sound.setBuffer(soundBuffer);
    if (!fightSoundBuffer.loadFromFile("../Data/fight-deep-voice-172194.wav")) {
        cerr << "Error loading fight sound!" << endl;
    }
    fightSound.setBuffer(fightSoundBuffer);
    
    // Tải nhạc nền
    if (!backgroundMusic.openFromFile("../Data/mrketid-127881.wav")) {
        cerr << "Error loading background music!" << endl;
    }
    backgroundMusic.setLoop(true);  // Lặp lại nhạc nền
    backgroundMusic.setVolume(95); // Điều chỉnh âm lượng nhạc nền nếu cần

    gameTitle.setFont(font);
    gameTitle.setString("Sky Warriors");
    gameTitle.setCharacterSize(80);  // Kích thước chữ lớn
    gameTitle.setFillColor(Color::White);  // Màu chữ trắng
    gameTitle.setPosition(width / 2 - gameTitle.getGlobalBounds().width / 2, height / 6);  // Vị trí tên game

    if (!soundOnTexture.loadFromFile("../Data/sound.png")) {
        cerr << "Error loading sound image!" << endl;
    }
    if (!soundOffTexture.loadFromFile("../Data/sound_off.png")) {
        cerr << "Error loading sound off image!" << endl;
    }
    soundOnSprite.setTexture(soundOnTexture);
    soundOffSprite.setTexture(soundOffTexture);

    // Đặt vị trí hình ảnh âm thanh
    soundOnSprite.setPosition(width - soundOnSprite.getGlobalBounds().width + 60, 20);  // Âm thanh bật ở góc phải
    soundOffSprite.setPosition(width - soundOffSprite.getGlobalBounds().width + 60, 20); // Âm thanh tắt ở góc phải
    soundOnSprite.setScale(0.5f, 0.5f);  // Thu nhỏ xuống 50%
    soundOffSprite.setScale(0.5f, 0.5f);

    soundEnabled = true; // Mặc định âm thanh bật



    std::string menuOptions[Max_main_menu] = { "Play", "Options", "About", "Exit" };
    for (int i = 0; i < Max_main_menu; i++) {
        mainMenu[i].setFont(font);
        mainMenu[i].setFillColor(Color::White);
        mainMenu[i].setString(menuOptions[i]);
        mainMenu[i].setCharacterSize(60);
        mainMenu[i].setPosition(width / 2 - mainMenu[i].getGlobalBounds().width / 2, height / 3 + i * 100);  // Vị trí menu
    }

    MainMenuSelected = 0;
    mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    background.setSize(Vector2f(width, height));  
    background.setFillColor(Color(0, 0, 0, 100)); 
}

void MainMenu::draw(RenderWindow& window) {
    window.draw(background);
    window.draw(gameTitle);
    for (int i = 0; i < Max_main_menu; ++i) {
        window.draw(mainMenu[i]);
    }
    if (soundEnabled)
        window.draw(soundOnSprite);
    else
        window.draw(soundOffSprite);
}


void MainMenu::MoveUp() {
    mainMenu[MainMenuSelected].setFillColor(Color::White);
    MainMenuSelected--;
    if (MainMenuSelected < 0)
        MainMenuSelected = Max_main_menu - 1;
    mainMenu[MainMenuSelected].setFillColor(Color::Blue);

    // Phát âm thanh khi di chuyển lên
    sound.play();
}

void MainMenu::MoveDown() {
    mainMenu[MainMenuSelected].setFillColor(Color::White);
    MainMenuSelected++;
    if (MainMenuSelected >= Max_main_menu)
        MainMenuSelected = 0;
    mainMenu[MainMenuSelected].setFillColor(Color::Blue);

    // Phát âm thanh khi di chuyển xuống
    sound.play();
}

int MainMenu::MainMenuPressed() {
    sound.play();
    if (MainMenuSelected == 0) {
          // Phát âm thanh fight khi chọn "Play"
        if (soundEnabled) {
            backgroundMusic.play();// Chỉ phát nhạc nền khi âm thanh được bật
            fightSound.play();     // Phát âm thanh fight khi chọn "Play"
        }
    }
    else if (MainMenuSelected == 1) {
        // Khi chọn "Options", toggle âm thanh
        toggleSound();
    }
    return MainMenuSelected;
}

void MainMenu::toggleSound() {
    soundEnabled = !soundEnabled;

    if (soundEnabled) {
        backgroundMusic.play();
        sound.setVolume(95);  // Khôi phục âm thanh hiệu ứng
    }
    else {
        backgroundMusic.stop();
        sound.setVolume(0);  // Tắt âm thanh hiệu ứng
    }
}

void MainMenu::handleInput(Event event, RenderWindow& window) {
    if (event.type == Event::KeyPressed) {
        // Kiểm tra phím Space để bật/tắt âm thanh trong "Options"
        if (event.key.code == Keyboard::Space) {
            if (MainMenuSelected == 1) {  // Nếu đang ở mục "Options"
                toggleSound();
            }
        }

        // Kiểm tra phím Enter để quay lại màn hình chính
        if (event.key.code == Keyboard::Enter) {
            if (MainMenuSelected == 1) {  // Nếu đang ở trong mục "Options"
                MainMenuSelected = 0;  // Quay lại mục "Play"
                mainMenu[MainMenuSelected].setFillColor(Color::Blue);  // Chọn lại mục "Play"
            }
        }
    }
}
void MainMenu::update(RenderWindow& window) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

        handleInput(event, window);  // Xử lý sự kiện
    }
}

