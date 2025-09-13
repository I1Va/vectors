#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

#include <iostream>

#include "geometry.hpp"
#include "visual.hpp"


const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const float VECTOR_ROTATION_SPEED = 0.001;


float sin_func(float x) {
    return std::sin(x);
}

int main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Plots");
    coordinate_system cordsys_big({100.0, 100.0}, {400.0, 400.0}, {70.0, 70.0}, 20);
    coordinate_system cordsys_small({450.0, 100.0}, {600.0, 250.0}, {30.0, 30.0}, 5);

    cordsys_big.link_child(&cordsys_small);

    oriented_vector or_vector({3, -3}, {1, 1});

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::Black);
    
        cordsys_big.draw_plot(window);
        cordsys_small.draw_plot(window);    

        cordsys_big.draw_func(window, &sin_func);
        cordsys_big.draw_vector(window, or_vector);
        
        or_vector = or_vector.rotate(VECTOR_ROTATION_SPEED);

        window.display();
    }
}


