// DesertShooter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Player.h"
#include "Weapon.h"

int main()
{
	TextureHolder textureHolderSingleton;

	sf::Texture playerTextureSheet = TextureHolder::GetTexture("graphics/players/tilemap_packed.png");
	Player player(playerTextureSheet);
	player.setPosition({ 1920.0f / 2, 1080.0f / 2 });

	sf::Texture weaponTexture = TextureHolder::GetTexture("graphics/weapons/tilemap_packed.png");
	Weapon weapon(weaponTexture, {-6, 10});
	weapon.attachTo(player, 24.0f);
	weapon.setAttributes(50, 300, 200);

	sf::Texture aimTexture = TextureHolder::GetTexture("graphics/ui/aim_01.png");
	sf::Sprite  aimSprite(aimTexture);
	aimSprite.setOrigin({ aimTexture.getSize().x / 2.0f, aimTexture.getSize().y / 2.0f });

	sf::VideoMode desktopVideoMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(desktopVideoMode, "Desert Shooter by Eric");
	window.setMouseCursorVisible(false);
	sf::Vector2f screenResolution(desktopVideoMode.size);
	
	sf::View camera;
	camera.setSize(screenResolution);
	camera.zoom(.3f);
	camera.setCenter(player.getPosition());

	sf::Clock clock;
	while (window.isOpen())
	{		
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}	

		sf::Time deltaTime = clock.restart();
		float delta = deltaTime.asSeconds();

		sf::Vector2f globalMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		player.update(delta);
		weapon.update(delta, globalMousePosition);
		aimSprite.setPosition(globalMousePosition);

		window.clear(sf::Color::Black);
		
		window.setView(camera);
		window.draw(player);
		window.draw(weapon);
		window.draw(aimSprite);

		window.display();
	}
}