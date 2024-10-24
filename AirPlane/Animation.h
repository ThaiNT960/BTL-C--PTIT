#pragma once
// Explosion.h
#include <SFML/Graphics.hpp>
#include <vector>

class Explosion {
public:
    Explosion(sf::Vector2f position);
    void render(sf::RenderWindow& window,float);
    bool isActive() const; 

private:
    std::vector<sf::Texture> textures; 
    sf::Sprite sprite;                   
    int currentSprite;                   
    bool active;
    float time;
};
