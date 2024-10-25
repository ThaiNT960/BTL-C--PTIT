#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
#define Max_main_menu 4

class MainMenu {
public:
    MainMenu(float width, float height);

    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int MainMenuPressed();

private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
};