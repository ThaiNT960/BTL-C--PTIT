#include "Score.h"

Score::Score() {
    score = 0;
    if (!font.loadFromFile("../Data/PressStart2P-Regular.TTF")) { 
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(18);        // kích thước 
    scoreText.setFillColor(Color::White);  // màu 
    scoreText.setPosition(10, 10);         // vị trí hiển thị
}

void Score::tăng(int tmp) {
    score += tmp;
}

void Score::reset() {
    score = 0;
}

void Score::render(sf::RenderWindow& window) {
    scoreText.setString("Score:" +to_string(score)); 
    window.draw(scoreText); 
}

int Score::getScore()  {
    return score;
}
