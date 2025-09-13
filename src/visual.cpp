#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "geometry.hpp"
#include "visual.hpp"

coordinate_system::coordinate_system
    (
        const geom_vector2 &frame_left,
        const geom_vector2 &frame_right,
        const geom_vector2 &axes_center,
        const int scale
    ):  frame_left(frame_left), 
        frame_right(frame_right), 
        axes_center(frame_left + axes_center), 
        scale(scale) 
    {
        width = frame_right.get_x() - frame_left.get_x();
        height = frame_right.get_y() - frame_left.get_y();
    };

void coordinate_system::draw_axis_mark_line(
        sf::RenderWindow &window, 
        const geom_vector2 &start, 
        const geom_vector2 &end)
{
    sf::VertexArray mark(sf::PrimitiveType::Lines, 2);

    mark[0].position = {start.get_x(), start.get_y()};
    mark[0].color = sf::Color::Black;

    mark[1].position = {end.get_x(), end.get_y()};
    mark[1].color = sf::Color::Black;

    window.draw(mark);  
}

void coordinate_system::draw_axis_marks(
        sf::RenderWindow &window, 
        const geom_vector2 center,
        const geom_vector2 x_start,
        const geom_vector2 x_end,
        const geom_vector2 y_start,
        const geom_vector2 y_end) {

    geom_vector2 x_axis_mark_delta(0, AXIS_MARK_DELTA);
    geom_vector2 y_axis_mark_delta(AXIS_MARK_DELTA, 0);
    
    for (geom_vector2 x = center; x >= x_start; x -= geom_vector2(scale, 0)) {
        draw_axis_mark_line(window, x + x_axis_mark_delta, x - x_axis_mark_delta);
    }
    for (geom_vector2 x = center; x <= x_end; x += geom_vector2(scale, 0)) {
        draw_axis_mark_line(window, x + x_axis_mark_delta, x - x_axis_mark_delta);
    }

    for (geom_vector2 y = center; y >= y_end; y -= geom_vector2(0, scale)) {
        
        draw_axis_mark_line(window, y + y_axis_mark_delta, y - y_axis_mark_delta);
    }
    for (geom_vector2 y = center; y <= y_start; y += geom_vector2(0, scale)) {
        draw_axis_mark_line(window, y + y_axis_mark_delta, y - y_axis_mark_delta);
    }
}

void coordinate_system::draw_axis(sf::RenderWindow &window, 
                const geom_vector2 &start,
                const geom_vector2 &end) {
    sf::VertexArray axis(sf::PrimitiveType::Lines, 2);

    axis[0].position = sf::Vector2f({start.get_x(), start.get_y()});
    axis[0].color = sf::Color::Black;
    axis[1].position = sf::Vector2f({end.get_x(), end.get_y()});
    axis[1].color = sf::Color::Black;

    window.draw(axis);
}

void coordinate_system::draw_triangle(
    sf::RenderWindow &window,
    const geom_vector2 &dot1,
    const geom_vector2 &dot2,
    const geom_vector2 &dot3) {
    sf::ConvexShape triangle;

    triangle.setPointCount(3);

    triangle.setPoint(0, {dot1.get_x(), dot1.get_y()}); 
    triangle.setPoint(1, {dot2.get_x(), dot2.get_y()}); 
    triangle.setPoint(2, {dot3.get_x(), dot3.get_y()});

    triangle.setFillColor(sf::Color::Black);

    window.draw(triangle);
}

void coordinate_system::draw_axes(sf::RenderWindow &window) {
    geom_vector2 y_axis_start(axes_center.get_x(), frame_right.get_y());
    geom_vector2 y_axis_end(axes_center.get_x(), frame_left.get_y());
    geom_vector2 x_axis_start(frame_left.get_x(), axes_center.get_y());
    geom_vector2 x_axis_end(frame_right.get_x(), axes_center.get_y());

    draw_axis(window, y_axis_start, y_axis_end); 
    draw_axis(window, x_axis_start, x_axis_end); 


    geom_vector2 x_axis_tr_dot1 = x_axis_end + geom_vector2(-AXIS_TRIANGLE_HEIGHT_DELTA, AXIS_TRIANGLE_BASE_DELTA);
    geom_vector2 x_axis_tr_dot2 = x_axis_end + geom_vector2(-AXIS_TRIANGLE_HEIGHT_DELTA, -AXIS_TRIANGLE_BASE_DELTA);
    geom_vector2 y_axis_tr_dot1 = y_axis_end + geom_vector2(AXIS_TRIANGLE_BASE_DELTA, AXIS_TRIANGLE_HEIGHT_DELTA);
    geom_vector2 y_axis_tr_dot2 = y_axis_end + geom_vector2(-AXIS_TRIANGLE_BASE_DELTA, AXIS_TRIANGLE_HEIGHT_DELTA);

    draw_triangle(window, x_axis_tr_dot1, x_axis_tr_dot2, x_axis_end);
    draw_triangle(window, y_axis_tr_dot1, y_axis_tr_dot2, y_axis_end);

    draw_axis_marks(window, axes_center, x_axis_start, x_axis_end - geom_vector2(AXIS_MARK_DELTA, 0), 
                                             y_axis_start, y_axis_end + geom_vector2(0, AXIS_MARK_DELTA));
}

bool coordinate_system::is_inside(const geom_vector2 &plot_dot) {
    if (plot_dot.get_x() > frame_right.get_x() ||
        plot_dot.get_x() < frame_left.get_x())
        return false;
    

    if (plot_dot.get_y() > frame_right.get_y() ||
        plot_dot.get_y() < frame_left.get_y())
        return false;

    return true; 
}

void coordinate_system::draw_plot(sf::RenderWindow &window) {
    sf::RectangleShape frame({float(width), float(height)});
    frame.setPosition({frame_left.get_x(), frame_left.get_y()});
    frame.setFillColor(sf::Color::White);
    
    window.draw(frame);
    draw_axes(window);
}
       
    
void coordinate_system::link_child(coordinate_system *clone) {
    children.push_back(clone);
}
                      

   
   
void coordinate_system::draw_func(sf::RenderWindow& window, float (*func)(float), bool pass_action){
    assert(func);

    if (pass_action) {
        for (coordinate_system *cs : children) {
            cs->draw_func(window, func, false);
        }
    }
    
    for (int x = 0; x < width; x++){
        float geom_x = (frame_left.get_x() + x - axes_center.get_x()) / scale;
        float geom_y = func(geom_x);

        geom_vector2 geom_dot(geom_x, geom_y);

        draw_dot(window, geom_dot);
    }
}

geom_vector2 coordinate_system::convert_to_pixel_cord(geom_vector2 dot) {
    dot = cord_mul(dot, geom_vector2(1, -1));
    dot *= scale;
    dot += axes_center;

    return dot;
}

void coordinate_system::draw_dot(sf::RenderWindow &window, geom_vector2 dot, bool pass_action) {
    sf::VertexArray dot_shape(sf::PrimitiveType::Points, 1);
    dot_shape[0].color = sf::Color::Black;

    if (pass_action) {
        for (coordinate_system *cs : children) {
            cs->draw_dot(window, dot, false);
        }
    }
    
    dot = convert_to_pixel_cord(dot);

    if (!is_inside(dot)) return;

    dot_shape[0].position = {dot.get_x(), dot.get_y()};
    window.draw(dot_shape);
}

void coordinate_system::draw_line(
    sf::RenderWindow &window, 
    geom_vector2 line_start, 
    geom_vector2 line_end,        
    bool pass_action
) { 

    if (pass_action) {
        for (coordinate_system *cs : children) {
            cs->draw_line(window, line_start, line_end, false);
        }
    }

    sf::VertexArray line_shape(sf::PrimitiveType::Lines, 2);
    line_start = convert_to_pixel_cord(line_start);
    line_end = convert_to_pixel_cord(line_end);

    line_shape[0].position = {line_start.get_x(), line_start.get_y()};
    line_shape[0].color = sf::Color::Black;

    line_shape[1].position = {line_end.get_x(), line_end.get_y()};
    line_shape[1].color = sf::Color::Black;

    window.draw(line_shape);  
}


void coordinate_system::draw_vector(
    sf::RenderWindow &window, 
    oriented_vector vector,     
    bool pass_action
) { 
    sf::VertexArray dot_shape(sf::PrimitiveType::Points, 1);
    dot_shape[0].color = sf::Color::Black;

    if (pass_action) {
        for (coordinate_system *cs : children) {
            cs->draw_vector(window, vector, false);
        }
    }
    
    geom_vector2 vector_begin = vector.get_begin();
    geom_vector2 vector_end = vector.get_end();

    draw_line(window, vector_begin, vector_end);

    
    geom_vector2 cur_vec = vector_begin - vector_end;

    
    geom_vector2 arrow_base = cur_vec * ARROW_BASE_SCALE;
    geom_vector2 arrow_perp = (cur_vec * ARROW_PERP_SCALE).rotate90();


    geom_vector2 arrow_left_part = arrow_base + arrow_perp;
    geom_vector2 arrow_right_part = arrow_base + arrow_perp * (-1);

    draw_line(window, vector_end, vector_end + arrow_left_part);
    draw_line(window, vector_end, vector_end + arrow_right_part);
}