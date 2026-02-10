// DesertShooter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Player.h"
#include "Weapon.h"
#include "ArenaManager.h"
#include "NineSliceTextureCoordinates.h"

int main()
{
	TextureHolder textureHolderSingleton;

	sf::Texture playerTextureSheet = TextureHolder::GetTexture("graphics/players/tilemap_packed.png");
	Player player(playerTextureSheet);
	player.setPosition({ 1920.0f / 2, 1080.0f / 2 });

	sf::Texture weaponTexture = TextureHolder::GetTexture("graphics/weapons/tilemap_packed.png");
	Weapon weapon(weaponTexture, {-6, 10});
	weapon.attachTo(player, 24.0f);
	weapon.setAttributes(50, 300, 300);

	sf::Texture aimTexture = TextureHolder::GetTexture("graphics/ui/aim_01.png");
	sf::Sprite  aimSprite(aimTexture);
	aimSprite.setOrigin({ aimTexture.getSize().x / 2.0f, aimTexture.getSize().y / 2.0f });

	sf::Texture arenaSpriteSheet = TextureHolder::GetTexture("graphics/tiles/tilemap_packed.png");		
	ArenaManager arena(arenaSpriteSheet);	
	
	NineSliceTextureCoordinates arenaTextCoords;
	arenaTextCoords.topLeftTextCoord  = { 0, 5 };
	arenaTextCoords.topTextCoord	  = { 1, 5 };
	arenaTextCoords.topRightTextCoord = { 2, 5 };

	arenaTextCoords.leftSideTextCoord  = { 0, 6 };
	arenaTextCoords.fillTextCoord	   = { 1, 6 };
	arenaTextCoords.rightSideTextCoord = { 2, 6 };

	arenaTextCoords.bottomLeftTextCoord  = { 0, 7 };
	arenaTextCoords.bottomTextCoord		 = { 1, 7 };
	arenaTextCoords.bottomRightTextCoord = { 2, 7 };
	
	arenaTextCoords.detailsTextCoord = { 3, 7 };


	float arenaSize = 300;
	arena.createRandomArena(arenaSize, arenaSize, arenaTextCoords);

	NineSliceTextureCoordinates fenceTextureCoordinates;
	fenceTextureCoordinates.topLeftTextCoord  = { 15, 9 };
	fenceTextureCoordinates.topTextCoord	  = { 16, 9 };
	fenceTextureCoordinates.topRightTextCoord = { 17, 9 };

	fenceTextureCoordinates.leftSideTextCoord  = { 15, 10 };
	fenceTextureCoordinates.fillTextCoord	   = { 16, 10 };
	fenceTextureCoordinates.rightSideTextCoord = { 17, 10 };

	fenceTextureCoordinates.bottomLeftTextCoord  = { 15, 11 };
	fenceTextureCoordinates.bottomTextCoord		 = { 16, 11 };
	fenceTextureCoordinates.bottomRightTextCoord = { 17, 11 };

	arena.createArenaOutline(arenaSize, arenaSize, fenceTextureCoordinates, 2);

	sf::Vector2f arenaCenter = player.getPosition();
	arenaCenter.x -= arenaSize/2;
	arenaCenter.y -= arenaSize/2;
	arena.setPosition(arenaCenter);

	//sf::IntRect arenaBounds({ {arenaCenter.x, arenaCenter.y}, {arenaSize, arenaSize}});

	sf::VideoMode desktopVideoMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(desktopVideoMode, "Desert Shooter by Eric");
	window.setMouseCursorVisible(false);
	sf::Vector2f screenResolution(desktopVideoMode.size);
	
	sf::View camera;
	camera.setSize(screenResolution);
	camera.zoom(.3f);

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
		camera.setCenter(player.getPosition());

		weapon.update(delta, globalMousePosition);
		aimSprite.setPosition(globalMousePosition);

		window.clear(sf::Color(0x52507AFF));
		
		window.setView(camera);
		window.draw(arena);
		window.draw(player);
		window.draw(weapon);
		window.draw(aimSprite);

		window.display();
	}
}
