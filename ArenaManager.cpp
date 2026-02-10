#include "ArenaManager.h"

void ArenaManager::fillTileMap(sf::VertexArray& vertices, float width, float height, NineSliceTextureCoordinates& textCoords, bool fillCenter, sf::Vector2f position)
{
	int cellWidth  = width / TILE_SIZE;
	int cellHeight = height / TILE_SIZE;

	srand(time(0));
	vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
	vertices.resize(static_cast<size_t>(width) * height * 6);

	for (int col = 0; col < cellWidth; ++col)
	{
		for (int row = 0; row < cellHeight; ++row)
		{
			if (!fillCenter && !(row == 0 || row == cellHeight - 1 || col == 0 || col == cellWidth - 1))
			{
				continue;
			}

			sf::Vertex* triangles = &vertices[(col + static_cast<size_t>(row) * width) * 6];

			triangles[0].position = { col * TILE_SIZE, row * TILE_SIZE };
			triangles[1].position = { col * TILE_SIZE, row * TILE_SIZE + TILE_SIZE };
			triangles[2].position = { col * TILE_SIZE + TILE_SIZE, row * TILE_SIZE };
			triangles[3].position = { col * TILE_SIZE + TILE_SIZE, row * TILE_SIZE };
			triangles[4].position = { col * TILE_SIZE + TILE_SIZE, row * TILE_SIZE + TILE_SIZE };
			triangles[5].position = { col * TILE_SIZE, row * TILE_SIZE + TILE_SIZE };

			triangles[0].position += position;
			triangles[1].position += position;
			triangles[2].position += position;
			triangles[3].position += position;
			triangles[4].position += position;
			triangles[5].position += position;

			sf::Vector2i result = getTextCoord(textCoords, row, col, cellWidth, cellHeight, fillCenter);
			int textCol = result.x;
			int textRow = result.y;

			triangles[0].texCoords = { textCol * TILE_SIZE, textRow * TILE_SIZE };
			triangles[1].texCoords = { textCol * TILE_SIZE, textRow * TILE_SIZE + TILE_SIZE };
			triangles[2].texCoords = { textCol * TILE_SIZE + TILE_SIZE, textRow * TILE_SIZE };
			triangles[3].texCoords = { textCol * TILE_SIZE + TILE_SIZE, textRow * TILE_SIZE };
			triangles[4].texCoords = { textCol * TILE_SIZE + TILE_SIZE, textRow * TILE_SIZE + TILE_SIZE };
			triangles[5].texCoords = { textCol * TILE_SIZE, textRow * TILE_SIZE + TILE_SIZE };
		}
	}
}

ArenaManager::ArenaManager(sf::Texture& texture) : m_SpriteSheetTexture(texture)
{
}

void ArenaManager::createRandomArena(float width, float height, NineSliceTextureCoordinates& textCoords, bool fillCenter)
{
	fillTileMap(m_Vertices, width, height, textCoords, fillCenter);	
}

void ArenaManager::createArenaOutline(float width, float height, NineSliceTextureCoordinates& outlineCoords, int tileOffset)
{
	width  -= tileOffset * TILE_SIZE;
	height -= tileOffset * TILE_SIZE;	
	fillTileMap(m_OutlineVertices, width, height, outlineCoords, false, { (tileOffset - 1) * TILE_SIZE, (tileOffset - 1) * TILE_SIZE });
}

sf::FloatRect ArenaManager::getArenaInnerOutlineBounds() const
{
	return m_OutlineVertices.getBounds();
}

sf::Vector2i ArenaManager::getTextCoord(NineSliceTextureCoordinates& textCoords, int row, int col, int cellWidth, int cellHeight, bool fillCenter)
{
	bool isTop    = row == 0;
	bool isBottom = row == cellHeight - 1;

	bool isLeft  = col == 0;
	bool isRight = col == cellWidth - 1;

	sf::Vector2i result;
	if (isTop)
	{
		if (isLeft)  return textCoords.topLeftTextCoord;
		if (isRight) return textCoords.topRightTextCoord;
		else		 return textCoords.topTextCoord;
	}
	if (isBottom)
	{
		if (isLeft)  return textCoords.bottomLeftTextCoord;
		if (isRight) return textCoords.bottomRightTextCoord;
		else		 return textCoords.bottomTextCoord;
	}

	if (isLeft)  return textCoords.leftSideTextCoord;
	if (isRight) return textCoords.rightSideTextCoord;

	float chance = (rand() % 101);

	if (chance < 5)
	{
		return textCoords.detailsTextCoord;
	}

	return textCoords.fillTextCoord;
}
