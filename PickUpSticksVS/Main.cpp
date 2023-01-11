#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

int main()
{
    //-----------------------------------------------------------------
    // Setup
    //-----------------------------------------------------------------

#pragma region Setup

    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::Fullscreen);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("Assets/Player_Stand.png"))
    {
        // error
        std::cout << "Texture load failed for 'Assets/Player_Stand.png'" << std::endl;
    }
    else
    {
        // success
        std::cout << "Texture 'Assets/Player_Stand.png' loaded successfully" << std::endl;
    }

    sf::Texture grassTexture;
    if (!grassTexture.loadFromFile("Assets/Grass.png"))
    {
        // error
        std::cout << "Texture load failed for 'Assets/Grass.png'" << std::endl;
    }
    else
    {
        // success
        std::cout << "Texture 'Assets/Grass.png' loaded successfully" << std::endl;
    }

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);

    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTexture);

    std::vector<sf::Sprite> grassVector;
    int numGrassToAdd = 15;
    for (int i = 0; i < numGrassToAdd; ++i)
    {
        grassVector.push_back(grassSprite);
        grassVector[i].setPosition((rand() % window.getSize().x + 0), (rand() % window.getSize().y + 0));
    }

# pragma endregion

    //-----------------------------------------------------------------
    // Event Polling
    //-----------------------------------------------------------------

#pragma region EventPolling

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
        }

#pragma endregion

        //-----------------------------------------------------------------
        // Drawing
        //-----------------------------------------------------------------

# pragma region Drawing

        window.clear(sf::Color(50, 150, 50));
        for (int i = 0; i < grassVector.size(); ++i)
        {
            window.draw(grassVector[i]);
        }

        window.draw(playerSprite);
        window.display();

    // Position Setup
    playerSprite.setPosition(sf::Vector2f(100.0f, 100.0f));

#pragma endregion


    }
    return 0;
}