#include "ParallexBackground.h"
#include "Layer.h"

void ParallexBackground::Init() {
    // Khởi tạo từng lớp nền với đường dẫn đến texture và tốc độ cuộn
    Layer* layer1 = new Layer();
    layer1->Init("../Data/1.png", 20.f); // Tốc độ cuộn: 20
    m_Background.push_back(layer1);

    Layer* layer2 = new Layer();
    layer2->Init("../Data/2.png", 40.f); // Tốc độ cuộn: 40
    m_Background.push_back(layer2);

    Layer* layer3 = new Layer();
    layer3->Init("../Data/3.png", 60.f); // Tốc độ cuộn: 60
    m_Background.push_back(layer3);

    Layer* layer4 = new Layer();
    layer4->Init("../Data/4.png", 80.f); // Tốc độ cuộn: 80
    m_Background.push_back(layer4);
}

void ParallexBackground::Update(float deltaTime) {
    // Cập nhật vị trí cho từng lớp nền
    for (auto& layer : m_Background) {
        layer->Update(deltaTime);
    }
}

void ParallexBackground::Render(sf::RenderWindow* window) {
    // Vẽ từng lớp nền lên cửa sổ, từ xa nhất đến gần nhất
    for (auto& layer : m_Background) {
        layer->Render(window);
    }
}
