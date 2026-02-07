// DesertShooter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Player.h"

int main()
{
	TextureHolder textureHolderSingleton;

	sf::Texture playerTextureSheet = TextureHolder::GetTexture("graphics/players/tilemap_packed.png");
	Player player(playerTextureSheet);

	sf::VideoMode desktopVideoMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(desktopVideoMode, "Desert Shooter by Eric");

	sf::Clock clock;
	while (window.isOpen())
	{		
		while (const std::optional event = window.pollEvent())
		{
			// "close requested" event: we close the window
			if (event->is<sf::Event::Closed>())
				window.close();
		}	

		sf::Time deltaTime = clock.restart();
		float delta = deltaTime.asSeconds();

		player.update(delta);

		window.clear(sf::Color::White);

		window.draw(player);

		window.display();
	}
}