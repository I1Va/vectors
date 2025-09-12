// #ifndef GEOMETRY_HPP
// #define GEOMETRY_HPP

// #include <SFML/Graphics.hpp>
// #include <SFML/System.hpp>
// #include <cmath>


// class geom_vector2 {
//     float x, y;
//     float len2;
// public:
//     geom_vector2(const float x, const float y): x(x), y(y) { len2 = NAN; }
//     geom_vector2 operator+(const geom_vector2 &other) const { return geom_vector2(x + other.x, y + other.y); }
//     geom_vector2 operator+=(const geom_vector2 &other) { 
//         len2 = NAN; 
//         x += other.x;
//         y += other.y;
//         return *this;
//     }

//     float get_x() const { return x; }
//     float get_y() const { return y; }
//     float get_len2() {
//         if (std::isnan(len2)) len2 = x * x + y * y;
//         return len2;
//     }
// };

// class coordinate_system {
//     geom_vector2 frame_left;
//     geom_vector2 frame_right;

//     geom_vector2 center;
//     float scale;

//     int width;
//     int height;

//     std::vector<coordinate_system *> children;

// private:
//     void make_axis(sf::VertexArray &dst_axis, const geom_vector2 &start, const geom_vector2 &end) {
//         dst_axis[0].position = sf::Vector2f({start.get_x(), start.get_y()});
//         dst_axis[0].color = sf::Color::Black;
//         dst_axis[1].position = sf::Vector2f({end.get_x(), end.get_y()});
//         dst_axis[1].color = sf::Color::Black;
//     }

//     void draw_triangle(sf::RenderWindow &window,
//                        const geom_vector2 &dot1,
//                        const geom_vector2 &dot2,
//                        const geom_vector2 &dot3) {
//         sf::ConvexShape triangle;

//         triangle.setPointCount(3);

//         triangle.setPoint(0, {dot1.get_x(), dot1.get_y()}); 
//         triangle.setPoint(1, {dot2.get_x(), dot2.get_y()}); 
//         triangle.setPoint(2, {dot3.get_x(), dot3.get_y()});

//         triangle.setFillColor(sf::Color::Black);

//         window.draw(triangle);
//     }

//     void draw_axes(sf::RenderWindow &window) {
//         geom_vector2 axes_center(frame_left + center);

//         geom_vector2 y_axis_start(axes_center.get_x(), frame_right.get_y());
//         geom_vector2 y_axis_end(axes_center.get_x(), frame_left.get_y());
//         geom_vector2 x_axis_start(frame_left.get_x(), axes_center.get_y());
//         geom_vector2 x_axis_end(frame_right.get_x(), axes_center.get_y());

//         sf::VertexArray y_axis(sf::PrimitiveType::Lines, 2);
//         sf::VertexArray x_axis(sf::PrimitiveType::Lines, 2);
//         make_axis(y_axis, y_axis_start, y_axis_end); 
//         make_axis(x_axis, x_axis_start, x_axis_end); 

//         window.draw(y_axis);
//         window.draw(x_axis);

//         geom_vector2 x_axis_tr_dot1 = x_axis_end + X_AXIS_TRIANGLE_DELTA1;
//         geom_vector2 x_axis_tr_dot2 = x_axis_end + X_AXIS_TRIANGLE_DELTA2;

//         draw_triangle(window, x_axis_tr_dot1, x_axis_tr_dot2, x_axis_end);

//     }
// public:
//     coordinate_system
//     (
//         const geom_vector2 &frame_left,
//         const geom_vector2 &frame_right,
//         const geom_vector2 &center,
//         const float scale
//     ): 
//         frame_left(frame_left),
//         frame_right(frame_right),
//         center(center),
//         scale(scale) 
//     {   
//         width = frame_right.get_x() - frame_left.get_x();
//         height = frame_right.get_y() - frame_left.get_y();
//         this->center += frame_left;          
//     }

//     void draw_plot(sf::RenderWindow &window) {
//         sf::RectangleShape frame({float(width), float(height)});
//         frame.setPosition({frame_left.get_x(), frame_left.get_y()});
//         frame.setFillColor(sf::Color::White);
        
//         window.draw(frame);
//         draw_axes(window);

       



//         // window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
//     }

                      

//     void draw_line() {
//         // cords transfrom
        
//         // cs draw
//         // children draw
//     }

//     void draw_dot() {
//         // аналогично
//     }


// };

// #endif // GEOMETRY_HPP