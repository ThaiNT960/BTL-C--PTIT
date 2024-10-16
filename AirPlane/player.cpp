#include "player.h"

Player::Player()
{
	if (!texture.loadFromFile("../Data/plane80.png")) {}
	sprite.setTexture(texture);
	sprite.setPosition(100, 300);
	speed = 400.f;
	canShoot = true;
}
void Player::shoot()
{
//Vị trí đạn bắn ra
	bullets.emplace_back(sprite.getPosition().x + sprite.getGlobalBounds().width,
		sprite.getPosition().y + sprite.getGlobalBounds().height / 2);
}
void Player::update(float t)
{
//Bắt phím di chuyển của người chơi
	if (Keyboard::isKeyPressed(Keyboard::W)&& sprite.getPosition().y- speed * t > 0) {
		sprite.move(0, -speed*t);
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)&& sprite.getPosition().y + sprite.getGlobalBounds().height+ speed * t <600) {
		sprite.move(0, speed*t);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)&& sprite.getPosition().x + sprite.getGlobalBounds().width+ speed * t < 800) {
		sprite.move(speed*t, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)&& sprite.getPosition().x- speed * t > 0) {
		sprite.move(-speed*t, 0);
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




