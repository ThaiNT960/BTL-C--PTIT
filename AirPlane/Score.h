#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;
class Score {
public:
    Score();
    void tăng(int tmp); // hàm tăng
    void reset(); // reset điểm
    void render(RenderWindow& window); 
    int getScore() ; // lấy điểm hiện tại
   void Reset();
private:
    int score; 
    Font font; 
    Text scoreText; 
};
