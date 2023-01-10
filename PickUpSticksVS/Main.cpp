#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::Titlebar | sf::Style::None);
    sf::CircleShape shape(150.f);
    shape.setFillColor(sf::Color(190, 211, 91));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}