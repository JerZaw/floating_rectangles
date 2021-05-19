#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <CustomRectangleShape.h>

int main() {
    srand(time(0));
    // create the window
    sf::RenderWindow window(sf::VideoMode(1200,800), "My window");

    // create some shapes
    std::vector<CustomRectangleShape> rectangles;

    for (int i=0; i<25; i++) {
        sf::Vector2f size(120.0, 60.0);
        sf::Vector2f position(std::rand() % (window.getSize().x - 120), std::rand() % (window.getSize().y - 60));
        rectangles.emplace_back(CustomRectangleShape(size, position));
    }

    for (auto &rec : rectangles) {
        rec.setFillColor(sf::Color(128,128,128));
        rec.setBounds(0, window.getSize().x, 0, window.getSize().y);
        rec.setSpeed(std::rand()%301-150,std::rand()%301-150,std::rand()%41-20);
    }


    // run the program as long as the window is open
    sf::Clock clock1;
    while (window.isOpen()) {

        sf::Time time1 = clock1.restart();
        for(auto &rec : rectangles) {
            rec.animate(time1);
        }

        sf::Event event;
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Button::Left){
                    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    for(auto &rec : rectangles) {
                        if(rec.getGlobalBounds().contains(mouse_position)){
                            rec.select();
                            rec.setFillColor(sf::Color(rand()%250,rand()%250,rand()%250));
                        }
                    }
                }
                else if(event.mouseButton.button == sf::Mouse::Button::Right){
                    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    for(auto &rec : rectangles) {
                        if(rec.getGlobalBounds().contains(mouse_position)){
                            rec.unselect();
                        }
                    }
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        for(const auto &rec : rectangles) {
            window.draw(rec);
        }

        // end the current frame
        window.display();
    }

    return 0;
}
