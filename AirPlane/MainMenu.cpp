#include "MainMenu.h"


MainMenu::MainMenu(float width, float height) {
    if (!font.loadFromFile("../Data/PressStart2P-Regular.TTF")) {}


    string menuOptions[Max_main_menu] = { "Play", "Options", "About", "Exit" };
    for (int i = 0; i < Max_main_menu; i++) {
        mainMenu[i].setFont(font);
        mainMenu[i].setFillColor(Color::White);
        mainMenu[i].setString(menuOptions[i]);
        mainMenu[i].setCharacterSize(50);
        mainMenu[i].setPosition(width / 2 - mainMenu[i].getGlobalBounds().width / 2, 200 + i * 100);
    }
    MainMenuSelected = 0;
    mainMenu[MainMenuSelected].setFillColor(Color::Blue);
}

void MainMenu::draw(RenderWindow& window) {
    for (int i = 0; i < Max_main_menu; ++i) {
        window.draw(mainMenu[i]);
    }
}

void MainMenu::MoveUp() {
    mainMenu[MainMenuSelected].setFillColor(Color::White);
    MainMenuSelected--;
    if (MainMenuSelected < 0)
        MainMenuSelected = Max_main_menu - 1;
    mainMenu[MainMenuSelected].setFillColor(Color::Blue);
}

void MainMenu::MoveDown() {
    mainMenu[MainMenuSelected].setFillColor(Color::White);
    MainMenuSelected++;
    if (MainMenuSelected >= Max_main_menu)
        MainMenuSelected = 0;
    mainMenu[MainMenuSelected].setFillColor(Color::Blue);
}
int MainMenu::MainMenuPressed() {
    return MainMenuSelected;
}