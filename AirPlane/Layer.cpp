#include "Layer.h"
#include <SFML/Graphics.hpp>

void Layer::Init(const std::string& name, float speed) {
    // Tải texture cho lớp nền
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(name);

    m_Image1.setTexture(*texture);
    m_Image2.setTexture(*texture);

    m_Speed = speed;
    m_SizeImage = static_cast<sf::Vector2i>(texture->getSize());

    // Thiết lập vị trí ban đầu cho 2 ảnh để tạo hiệu ứng cuộn liên tục
    m_Image1.setPosition(sf::Vector2f(0, 0));
    m_Image2.setPosition(sf::Vector2f(m_SizeImage.x, 0));
}

void Layer::Update(float deltaTime) {
    // Di chuyển ảnh từ phải qua trái với tốc độ quy định
    m_Image1.move(-m_Speed * deltaTime, 0);
    m_Image2.move(-m_Speed * deltaTime, 0);

    // Kiểm tra vị trí và tái thiết lập để tạo hiệu ứng cuộn
    if (m_Image1.getPosition().x <= -m_SizeImage.x) {
        m_Image1.setPosition(m_SizeImage.x, 0);
    }
    if (m_Image2.getPosition().x <= -m_SizeImage.x) {
        m_Image2.setPosition(m_SizeImage.x, 0);
    }
}

void Layer::Render(sf::RenderWindow* window) {
    // Vẽ cả hai ảnh để tạo hiệu ứng cuộn liên tục
    window->draw(m_Image1);
    window->draw(m_Image2);
}
