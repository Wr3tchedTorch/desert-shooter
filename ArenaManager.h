#pragma once
#include <SFML/Graphics.hpp>
#include "NineSliceTextureCoordinates.h";

class ArenaManager : public sf::Drawable, public sf::Transformable
{
private:
	const float TILE_SIZE = 16.0f;

	sf::VertexArray m_Vertices;
    sf::VertexArray m_OutlineVertices;
    sf::Texture& m_SpriteSheetTexture;
	        
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.texture    = &m_SpriteSheetTexture;
        states.transform *= getTransform();
        target.draw(m_Vertices, states);
        target.draw(m_OutlineVertices, states);
    }

    void fillTileMap(sf::VertexArray& vertices, float width, float height, NineSliceTextureCoordinates& textCoords, bool fillCenter = true, sf::Vector2f position = {0, 0});

public:
    ArenaManager(sf::Texture& texture);
    
    void createRandomArena(
        float width,
        float height,
        NineSliceTextureCoordinates& textCoords,
        bool fillCenter = true
    );

    void createArenaOutline(float width, float height, NineSliceTextureCoordinates& outlineCoords, int tileOffset);
    sf::FloatRect getArenaInnerOutlineBounds() const;

    sf::Vector2i getTextCoord(NineSliceTextureCoordinates& textCoords, int row, int col, int cellWidth, int cellHeight, bool fillCenter);
};


