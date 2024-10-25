#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Explosion {
public:
    Explosion(Vector2f position);
    void render(RenderWindow& window, float);
    bool isActive() const;

private:
    vector<Texture> textures;
    Sprite sprite;
    int currentSprite;
    bool active;
    float time;
};