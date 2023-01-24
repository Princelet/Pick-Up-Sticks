#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

void SetupText(sf::Text &text, sf::Font &font)
{
    text.setFont(font);
    text.setFillColor(sf::Color::Cyan);
    text.setOutlineThickness(2.0f);
    text.setOutlineColor(sf::Color::Black);
}

void LoadAsset(sf::Texture &slot, std::string asset)
{
    if (!slot.loadFromFile(asset))
    {
        // error
        std::cout << "Texture load failed for '" + asset + "'" << std::endl;
    }
    else
        std::cout << "Texture '" + asset + "' loaded successfully" << std::endl;
}

void LoadAsset(sf::Font &slot, std::string asset)
{
    if (!slot.loadFromFile(asset))
    {
        // error
        std::cout << "Font load failed for '" + asset + "'" << std::endl;
    }
    else
        std::cout << "Font '" + asset + "' loaded successfully" << std::endl;
}

void LoadAsset(sf::SoundBuffer& slot, std::string asset)
{
    if (!slot.loadFromFile(asset))
    {
        // error
        std::cout << "Sound load failed for '" + asset + "'" << std::endl;
    }
    else
        std::cout << "Sound '" + asset + "' loaded successfully" << std::endl;
}

void LoadAsset(sf::Music& slot, std::string asset)
{
    if (!slot.openFromFile(asset))
    {
        // error
        std::cout << "Music load failed for '" + asset + "'" << std::endl;
    }
    else
        std::cout << "Music '" + asset + "' loaded successfully" << std::endl;

    slot.setVolume(50);
    slot.setLoop(true);
}

void SetTexture(sf::Sprite &slot, sf::Texture &texture)
{
    slot.setTexture(texture);
    slot.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

int main()
{
    //-----------------------------------------------------------------
    // Setup
    //-----------------------------------------------------------------

#pragma region Setup

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::None);

    int scoreValue = 0;

    sf::Texture playerTexture;
    LoadAsset(playerTexture, "Assets/Player_Stand.png");
    sf::Texture grassTexture;
    LoadAsset(grassTexture, "Assets/Grass.png");
    sf::Texture stickTexture;
    LoadAsset(stickTexture, "Assets/Stick.png");

    sf::Sprite playerSprite;
    SetTexture(playerSprite, playerTexture);
    sf::Sprite grassSprite;
    SetTexture(grassSprite, grassTexture);
    sf::Sprite stickSprite;
    SetTexture(stickSprite, stickTexture);


    // Position setup
    playerSprite.setPosition(window.getSize().x/2, window.getSize().y/2);

    // Colour setup
    //playerSprite.setColor(sf::Color(0, 200, 150));

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
    LoadAsset(gameFont, "Assets/GameFont.ttf");
    
    // Create text objects
    sf::Text gameTitle;
    SetupText(gameTitle, gameFont);
    gameTitle.setString("Pick Up Sticks");
    gameTitle.setPosition((window.getSize().x/2.0f) - (gameTitle.getLocalBounds().width/2.0f), 75.0f);

    sf::Text scoreText;
    SetupText(scoreText, gameFont);
    scoreText.setString("Score: " + scoreValue);
    scoreText.setPosition(75.0f, 75.0f);


    // Load Sound
    sf::SoundBuffer buffer;

    LoadAsset(buffer, "Assets/Start.wav");
    sf::Sound startSound;
    startSound.setBuffer(buffer);
    startSound.play();

    LoadAsset(buffer, "Assets/Pickup.wav");
    sf::Sound stickSound;
    stickSound.setBuffer(buffer);
    stickSound.setPitch((5 + rand() % 10) / 10.0f);


    // Stream Music
    sf::Music gameMusic;
    LoadAsset(gameMusic, "Assets/Music.ogg");
    gameMusic.play();


    bool dashState = false;
    int lastXDir = 0;
    int lastYDir = 0;


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
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

#pragma endregion

        //-----------------------------------------------------------------
        // Update
        //-----------------------------------------------------------------

#pragma region Update

        sf::Vector2f direction(0, 0);
        if (sf::Joystick::isConnected(1))
        {
            float axisX = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
            float axisY = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);

            float deadzone = 0;

            if (abs(axisX) > deadzone)
                direction.x = axisX / 100.0f;
            if (abs(axisY) > deadzone)
                direction.y = axisY / 100.0f;
        }
        
        if (dashState == false && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(1, 0)))
        {
            switch (lastXDir)
            {
                case 1:
                {
                    direction.x = -1500;
                    break;
                }
                case 2:
                {
                    direction.x = 1500;
                    break;
                }
                default:
                {
                    direction.x = 0;
                    break;
                }
            }
            switch (lastYDir)
            {
            case 1:
            {
                direction.y = -1500;
                break;
            }
            case 2:
            {
                direction.y = 1500;
                break;
            }
            default:
            {
                direction.y = 0;
                break;
            }
            }
            dashState = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == false && sf::Joystick::isButtonPressed(1, 0) == false)
        {
            dashState = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            direction.x = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            direction.x = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            direction.y = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            direction.y = 1;
        }
        
        if (direction.x < 0)
        {
            lastXDir = 1;
        }
        if (direction.x > 0)
        {
            lastXDir = 2;
        }
        if (direction.y < 0)
        {
            lastYDir = 1;
        }
        if (direction.y > 0)
        {
            lastYDir = 2;
        }

        playerSprite.move(direction*0.1f);


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // Get Mouse Position
            sf::Vector2i localPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosFloat = (sf::Vector2f)localPos;

            // Spawn Stick at Location
            stickSprite.setPosition(mousePosFloat);
            stickVector.push_back(stickSprite);
        }


        // Bump off wall and increase score
        if (playerSprite.getPosition().x < 0)
        {
            playerSprite.setPosition(playerSprite.getPosition().x + 150.0f, playerSprite.getPosition().y);
            scoreValue++;
            stickSound.play();
        }
        if (playerSprite.getPosition().x > (window.getSize().x))
        {
            playerSprite.setPosition(playerSprite.getPosition().x - 150.0f, playerSprite.getPosition().y);
            scoreValue++;
            stickSound.play();
        }
        if (playerSprite.getPosition().y < 0)
        {
            playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y + 150.0f);
            scoreValue++;
            stickSound.play();
        }
        if (playerSprite.getPosition().y > (window.getSize().y))
        {
            playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y - 150.0f);
            scoreValue++;
            stickSound.play();
        }


        scoreText.setString("Score: " + std::to_string(scoreValue));


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
        window.display();

#pragma endregion


    }
    return 0;
}
