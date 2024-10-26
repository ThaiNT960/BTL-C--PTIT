#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#include "Layer.h"

class ParallexBackground {
public:
    // Khởi tạo các lớp nền
    void Init();
    // Cập nhật vị trí của các lớp nền
    void Update(float deltaTime);
    // Vẽ các lớp nền lên cửa sổ
    void Render(sf::RenderWindow* window);

private:
    std::list<Layer*> m_Background; // Lưu trữ các lớp nền
};
