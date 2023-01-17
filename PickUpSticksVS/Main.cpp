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

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::Fullscreen);

    int scoreValue = 0;

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("Assets/Player_Stand.png"))
    {
        // error
        std::cout << "Texture load failed for 'Assets/Player_Stand.png'" << std::endl;
    }
    else
        std::cout << "Texture 'Assets/Player_Stand.png' loaded successfully" << std::endl;

    sf::Texture grassTexture;
    if (!grassTexture.loadFromFile("Assets/Grass.png"))
    {
        // error
        std::cout << "Texture load failed for 'Assets/Grass.png'" << std::endl;
    }
    else
        std::cout << "Texture 'Assets/Grass.png' loaded successfully" << std::endl;

    sf::Texture stickTexture;
    if (!stickTexture.loadFromFile("Assets/Stick.png"))
    {
        // error
        std::cout << "Texture load failed for 'Assets/Stick.png'" << std::endl;
    }
    else
        std::cout << "Texture 'Assets/Stick.png' loaded successfully" << std::endl;


    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    playerSprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTexture);
    grassSprite.setOrigin(grassTexture.getSize().x / 2, grassTexture.getSize().y / 2);
    sf::Sprite stickSprite;
    stickSprite.setTexture(stickTexture);
    stickSprite.setOrigin(stickTexture.getSize().x / 2, stickTexture.getSize().y / 2);


    // Colour setup
    playerSprite.setColor(sf::Color(190, 150, 230));

    // Rotation example
    playerSprite.setRotation(90);

    // Scale example
    //playerSprite.setScale(4.0f, 0.75f);


    // Position setup
    std::vector<sf::Sprite> grassVector;
    int numGrassToAdd = 15;
    for (int i = 0; i < numGrassToAdd; ++i)
    {
        float grassScale = (float)(0.5 + rand() % 10) / 10.0f;
        grassVector.push_back(grassSprite);
        grassVector[i].setPosition((rand() % window.getSize().x - grassTexture.getSize().x), (rand() % window.getSize().y - grassTexture.getSize().y));
        grassVector[i].setColor(sf::Color(100 + rand() % 100, 30 + rand() % 200, 100 + rand() % 50)); 
        grassVector[i].setScale(grassScale, grassScale);
    }

    std::vector<sf::Sprite> stickVector;
    stickSprite.setPosition((rand() % window.getSize().x - stickTexture.getSize().x), (rand() % window.getSize().y - stickTexture.getSize().y));
    stickSprite.setRotation((float)(rand() % 360));
    stickVector.push_back(stickSprite);


    // Load Fonts
    sf::Font gameFont;
    gameFont.loadFromFile("Assets/GameFont.ttf");

    // Create text objects
    sf::Text gameTitle;
    gameTitle.setFont(gameFont);
    gameTitle.setString("Pick Up Sticks");
    float textWidth = gameTitle.getLocalBounds().width;
    gameTitle.setPosition((window.getSize().x/2.0f) - textWidth/2.0f, 75.0f);

    sf::Text scoreText;
    scoreText.setFont(gameFont);
    scoreText.setString("Score: ");
    scoreText.setPosition(75.0f, 75.0f);

    sf::Text scoreVal;
    scoreVal.setFont(gameFont);
    scoreVal.setString("value here");
    scoreVal.setPosition(250.0f, 75.0f);



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
            window.draw(grassVector[i]);
        for (int i = 0; i < stickVector.size(); ++i)
            window.draw(stickVector[i]);
        window.draw(playerSprite);

        window.draw(gameTitle);
        window.draw(scoreText);
        window.draw(scoreVal);
        window.display();

    // Position Setup
    playerSprite.setPosition(sf::Vector2f(100.0f, 100.0f));

#pragma endregion


    }
    return 0;
}