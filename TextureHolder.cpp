#include "TextureHolder.h"

#include <assert.h>

TextureHolder* TextureHolder::m_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_Instance == nullptr);
	m_Instance = this;
}

const Texture& TextureHolder::GetTexture(const string& filepath)
{
	unordered_map<string, Texture>::iterator result = m_Instance->m_Textures.find(filepath);

	if (result == m_Instance->m_Textures.end())
	{
		bool success = m_Instance->m_Textures[filepath].loadFromFile(filepath);		
	}

	return m_Instance->m_Textures[filepath];
}
