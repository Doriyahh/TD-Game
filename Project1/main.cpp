#include <SFML/Graphics.hpp>
#include "Map.hpp"

int main()
{
    /*sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
   sf::CircleShape shape(100.f);
   shape.setFillColor(sf::Color::Green);

   while (window.isOpen())
   {
       while (const std::optional event = window.pollEvent())
       {
           if (event->is<sf::Event::Closed>())
               window.close();
       }

       window.clear();
       window.draw(shape);
       window.display();
   }*/

    sf::RenderWindow window(sf::VideoMode({ 1200, 900 }), "Tower Defense Game");

    Map map;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        map.draw(window);

        window.display();
    }

    return 0;
}