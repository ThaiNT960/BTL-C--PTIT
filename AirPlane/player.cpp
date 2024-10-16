#include "player.h"

Player::Player()
{
	if (!texture.loadFromFile("../Data/plane80.png")) {}
	sprite.setTexture(texture);
	sprite.setPosition(100, 300);
	speed = 0.4f;
	canShoot = true;
}
void Player::shoot()
{
//Vi tri đạn đc bắn ra
	bullets.emplace_back(sprite.getPosition().x + sprite.getGlobalBounds().width,
		sprite.getPosition().y + sprite.getGlobalBounds().height / 2);
}
void Player::update()
{
//Quan ly di chuyen
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		sprite.move(0, -speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		sprite.move(0, speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		sprite.move(speed, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		sprite.move(-speed, 0);
	}
//Gioi han di chuyen

	Vector2f vitri = sprite.getPosition(); // lấy vị trí hiện tại

	// di chuyển lên trên 
	if (vitri.y < 0) {
		sprite.setPosition(vitri.x, 0); 
	}
	// di chuyển xuống dưới 
	if (vitri.y + sprite.getGlobalBounds().height > 843) {
		sprite.setPosition(vitri.x, 843 - sprite.getGlobalBounds().height);
	}
	//  di chuyển sang trái 
	if (vitri.x < 0) {
		sprite.setPosition(0, vitri.y); 
	}
	//  di chuyển sang phải 
	if (vitri.x + sprite.getGlobalBounds().width > 1500) {
		sprite.setPosition(1500 - sprite.getGlobalBounds().width, vitri.y);
	}


// Kiểm tra việc bắn đạn
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canShoot) {
		   shoot();   
		canShoot = false; 
	}
// Kiểm tra khi nào nhả phím Space
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		canShoot = true; // Khi nhả phím, cho phép bắn đạn lần tiếp theo
	}

 //Cập nhật vị trí các viên đạn
	for (auto& bullet : bullets) {
		bullet.update(); // Goi ham update trong bullet.h
	}



}
void Player::render(RenderWindow& window)
{
	window.draw(sprite);
	for ( auto& bullet : bullets) {
		bullet.render(window);
	}
	
}




