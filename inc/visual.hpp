#ifndef VISUAL_H
#define VISUAL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <geometry.hpp>


static float AXIS_TRIANGLE_BASE_DELTA = 4;
static float AXIS_TRIANGLE_HEIGHT_DELTA = 7;
static float AXIS_MARK_DELTA = 2;

static float ARROW_BASE_SCALE = 0.3;
static float ARROW_PERP_SCALE = 0.05;


class coordinate_system {
    geom_vector2 frame_left;
    geom_vector2 frame_right;

    geom_vector2 axes_center;
    
    int scale;

    int width;
    int height;

    std::vector<coordinate_system*> children;

private:
    void draw_axis_mark_line(
            sf::RenderWindow &window, 
            const geom_vector2 &start, 
            const geom_vector2 &end);

    void draw_axis_marks(
            sf::RenderWindow &window, 
            const geom_vector2 center,
            const geom_vector2 x_start,
            const geom_vector2 x_end,
            const geom_vector2 y_start,
            const geom_vector2 y_end);

    void draw_axis(sf::RenderWindow &window, 
                   const geom_vector2 &start,
                   const geom_vector2 &end);

    void draw_triangle(
        sf::RenderWindow &window,
        const geom_vector2 &dot1,
        const geom_vector2 &dot2,
        const geom_vector2 &dot3);

    void draw_axes(sf::RenderWindow &window);

    bool is_inside(const geom_vector2 &plot_dot);

public:
    coordinate_system
    (
        const geom_vector2 &frame_left,
        const geom_vector2 &frame_right,
        const geom_vector2 &axes_center,
        const int scale
    );

    void draw_plot(sf::RenderWindow &window);
    
    void link_child(coordinate_system *clone);
   
    void draw_func(sf::RenderWindow& window, float (*func)(float), bool pass_action=true);

    geom_vector2 convert_to_pixel_cord(geom_vector2 dot);

    void draw_dot(sf::RenderWindow &window, geom_vector2 dot, bool pass_action=true);
    void draw_line(
        sf::RenderWindow &window, 
        geom_vector2 line_start, 
        geom_vector2 line_end,        
        bool pass_action=true
    );


    void draw_vector(
        sf::RenderWindow &window, 
        oriented_vector vector,      
        bool pass_action=true
    );

};


#endif // VISUAL_H