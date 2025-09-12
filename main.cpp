#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>


const static int WINDOW_WIDTH = 800;
const static int WINDOW_HEIGHT = 600;

const static float AXIS_TRIANGLE_BASE_DELTA = 4;
const static float AXIS_TRIANGLE_HEIGHT_DELTA = 7;
const static float AXIS_MARK_DELTA = 2;

const static float ARROW_BASE_SCALE = 0.3;
const static float ARROW_PERP_SCALE = 0.05;

class geom_vector2 {
    float x, y;
    float len2;
public:
    geom_vector2(const float x, const float y): x(x), y(y) { len2 = NAN; }
    geom_vector2 operator+(const geom_vector2 &other) const { return geom_vector2(x + other.x, y + other.y); }
    geom_vector2 operator*(const float scalar) const { return geom_vector2(x * scalar, y * scalar); }
    geom_vector2 operator-(const geom_vector2 &other) const { return geom_vector2(x - other.x, y - other.y); }
    geom_vector2 operator+=(const geom_vector2 &other) { 
        len2 = NAN; 
        x += other.x;
        y += other.y;
        return *this;
    }
     geom_vector2 operator*=(const float scalar) { 
        len2 = NAN; 
        x *= scalar;
        y *= scalar;
        return *this;
    }

    geom_vector2 operator-=(const geom_vector2 &other) { 
        len2 = NAN; 
        x -= other.x;
        y -= other.y;
        return *this;
    }

    geom_vector2 rotate90() const {
        return geom_vector2(-y, x);
    }
    
    bool operator<(const geom_vector2 &other) const { return x < other.x && y < other.y; }
    bool operator<=(const geom_vector2 &other) const { return x <= other.x && y <= other.y; }
    bool operator>(const geom_vector2 &other) const { return x > other.x && y > other.y; }
    bool operator>=(const geom_vector2 &other) const { return x >= other.x && y >= other.y; }

      

    float get_x() const { return x; }
    float get_y() const { return y; }
    float get_len2() {
        if (std::isnan(len2)) len2 = x * x + y * y;
        return len2;
    }
};

std::ostream &operator<<(std::ostream &stream, const geom_vector2 &vec) {
    stream << "{" << vec.get_x() << ", " << vec.get_y() << "}\n"; 
    return stream;
}

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
            const geom_vector2 &end)
    {
        sf::VertexArray mark(sf::PrimitiveType::Lines, 2);

        mark[0].position = {start.get_x(), start.get_y()};
        mark[0].color = sf::Color::Black;

        mark[1].position = {end.get_x(), end.get_y()};
        mark[1].color = sf::Color::Black;

        window.draw(mark);  
    }

    void draw_axis_marks(
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
    void draw_axis(sf::RenderWindow &window, 
                   const geom_vector2 &start,
                   const geom_vector2 &end) {
        sf::VertexArray axis(sf::PrimitiveType::Lines, 2);

        axis[0].position = sf::Vector2f({start.get_x(), start.get_y()});
        axis[0].color = sf::Color::Black;
        axis[1].position = sf::Vector2f({end.get_x(), end.get_y()});
        axis[1].color = sf::Color::Black;

        window.draw(axis);
    }

    void draw_triangle(
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

    void draw_axes(sf::RenderWindow &window) {
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

    bool is_inside(const geom_vector2 &plot_dot) {
        if (plot_dot.get_x() > frame_right.get_x() ||
            plot_dot.get_x() < frame_left.get_x())
            return false;
        

        if (plot_dot.get_y() > frame_right.get_y() ||
            plot_dot.get_y() < frame_left.get_y())
            return false;

        return true; 
    }

public:
    coordinate_system
    (
        const geom_vector2 &frame_left,
        const geom_vector2 &frame_right,
        const geom_vector2 &axes_center,
        const int scale
    ): 
        frame_left(frame_left),
        frame_right(frame_right),
        axes_center(axes_center),
        scale(scale) 
    {   
        width = frame_right.get_x() - frame_left.get_x();
        height = frame_right.get_y() - frame_left.get_y();
        this->axes_center += frame_left;          
    }

    void draw_plot(sf::RenderWindow &window) {
        sf::RectangleShape frame({float(width), float(height)});
        frame.setPosition({frame_left.get_x(), frame_left.get_y()});
        frame.setFillColor(sf::Color::White);
        
        window.draw(frame);
        draw_axes(window);
        

       



        // window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    }
    
    void link_child(coordinate_system *clone) {
        children.push_back(clone);
    }
                      

   
   
    void draw_func(sf::RenderWindow& window, float (*func)(float), bool pass_action=true){
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

    geom_vector2 convert_to_pixel_cord(geom_vector2 dot) {
        dot *= scale;
        dot += axes_center;
        return dot;
    }

    void draw_dot(sf::RenderWindow &window, geom_vector2 dot, bool pass_action=true) {
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

    void draw_line(
        sf::RenderWindow &window, 
        geom_vector2 line_start, 
        geom_vector2 line_end,        
        bool pass_action=true
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


    void draw_vector(
        sf::RenderWindow &window, 
        geom_vector2 vector_start, 
        geom_vector2 vector_end,        
        bool pass_action=true
    ) { 
        sf::VertexArray dot_shape(sf::PrimitiveType::Points, 1);
        dot_shape[0].color = sf::Color::Black;

        if (pass_action) {
            for (coordinate_system *cs : children) {
                cs->draw_vector(window, vector_start, vector_end, false);
            }
        }
        
        draw_line(window, vector_start, vector_end);


        geom_vector2 cur_vec = vector_start - vector_end;

        
        geom_vector2 arrow_base = cur_vec * ARROW_BASE_SCALE;
        geom_vector2 arrow_perp = (cur_vec * ARROW_PERP_SCALE).rotate90();

       

        geom_vector2 arrow_left_part = arrow_base + arrow_perp;
        geom_vector2 arrow_right_part = arrow_base + arrow_perp * (-1);

        draw_line(window, vector_end, vector_end + arrow_left_part);
        draw_line(window, vector_end, vector_end + arrow_right_part);
    
    }

};






float sin_func(float x) {
    return std::sin(x);
}

int main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Plots");
    coordinate_system cordsys_big({100.0, 100.0}, {400.0, 400.0}, {70.0, 70.0}, 20);
    coordinate_system cordsys_small({450.0, 100.0}, {600.0, 250.0}, {30.0, 30.0}, 5);

    cordsys_big.link_child(&cordsys_small);

    // PlotWidget *big_plot = new PlotWidget(&window, {50, 50}, {550, 550}, {50, 50}, 10);
    // PlotWidget *small_plot = new PlotWidget(&window, {600, 400}, {750, 550}, {50, 50}, 10);


    // window.clear(sf::Color::White);

    

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.clear(sf::Color::White);

        cordsys_big.draw_plot(window);
        cordsys_small.draw_plot(window);

        

        // cordsys_big.draw_func(window, &sin_func);
        cordsys_big.draw_vector(window, {5, 5}, {8, 10});

        
        // cordsys_big.draw_dot(window, {10, 0});

        // draw_sin_func(window, cordsys_big);


        // plot1.drawPlot(window);
        // plot2.drawPlot(window);

        // plot1.drawFunc(window, &linear);
        // plot1.drawFunc(window, &Mysin);

        // plot2.drawFunc(window, &linear);
        // plot2.drawFunc(window, &Mysin);

        // updateVec(vec);
        // plot1.drawVec(window, {0, 0}, vec);

        window.display();
    }
}


