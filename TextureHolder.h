#pragma once
#ifndef TEXTURE_HOLDER_h
#define TEXTURE_HOLDER_h

#include "SFML/Graphics/Texture.hpp"
#include <iostream>
#include <unordered_map>

using sf::Texture;

using std::unordered_map, std::string;

class TextureHolder
{
private:
	unordered_map<string, Texture> m_Textures;

	static TextureHolder* m_Instance;

public:
	TextureHolder();
	static const Texture& GetTexture(const string& filepath);
};

#endif