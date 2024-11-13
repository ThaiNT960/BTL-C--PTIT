#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
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
    void toggleSound();
    Music& getBackgroundMusic() { return backgroundMusic; }
    void handleInput(Event event, RenderWindow& window);
    void update(sf::RenderWindow& window);


private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
    Text gameTitle;
    SoundBuffer soundBuffer;
    Sound sound;
    RectangleShape background;
    SoundBuffer fightSoundBuffer; 
    Sound fightSound;
    Music backgroundMusic;
    Texture soundOnTexture;
    Texture soundOffTexture;
    Sprite soundOnSprite;
    Sprite soundOffSprite;
    bool soundEnabled;
};
