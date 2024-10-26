#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Layer {
public:
    // Khởi tạo lớp với tên file texture và tốc độ cuộn
    void Init(const std::string& name, float speed);
    // Cập nhật vị trí lớp nền dựa trên deltaTime
    void Update(float deltaTime);
    // Vẽ lớp nền lên cửa sổ
    void Render(sf::RenderWindow* window);

private:
    sf::Sprite m_Image1; // Ảnh chính cho lớp nền
    sf::Sprite m_Image2; // Ảnh thứ hai để tạo hiệu ứng cuộn
    sf::Vector2i m_SizeImage; // Kích thước ảnh
    float m_Speed; // Tốc độ di chuyển của lớp
};
