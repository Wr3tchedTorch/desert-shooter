#pragma once
#include <SFML/Graphics.hpp>

class NineSliceTextureCoordinates
{
public:
    sf::Vector2i fillTextCoord = { -1, -1 };
    
    sf::Vector2i rightSideTextCoord = {-1, -1};
    sf::Vector2i leftSideTextCoord  = {-1, -1};
    sf::Vector2i bottomTextCoord    = {-1, -1};
    sf::Vector2i topTextCoord       = {-1, -1};

    sf::Vector2i topRightTextCoord    = {-1, -1};
    sf::Vector2i topLeftTextCoord     = {-1, -1};
    sf::Vector2i bottomRightTextCoord = {-1, -1};
    sf::Vector2i bottomLeftTextCoord  = {-1, -1};

    sf::Vector2i detailsTextCoord = {-1, -1};
};

