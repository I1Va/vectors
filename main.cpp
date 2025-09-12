#include <SFML/Graphics.hpp>
#include <math.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


class geom_vector2 {
    float x, y;
    float len2;
public:
    geom_vector2(const float x, const float y): x(x), y(y) { len2 = NAN; }
    geom_vector2 operator+(const geom_vector2 &other) const { return geom_vector2(x + other.x, y + other.y); }
    geom_vector2 operator+=(const geom_vector2 &other) { 
        len2 = NAN; 
        x += other.x;
        y += other.y;
        return *this;
    }

    float get_x() const { return x; }
    float get_y() const { return y; }
    float get_len2() {
        if (std::isnan(len2)) len2 = x * x + y * y;
        return len2;
    }
};

class coordinate_system {
    geom_vector2 frame_left;
    geom_vector2 frame_right;

    geom_vector2 center;
    float scale;

    int width;
    int height;

    std::vector<coordinate_system *> children;

private:
    void make_axis(sf::VertexArray &dst_axis, const geom_vector2 &start, const geom_vector2 &end) {
        dst_axis[0].position = sf::Vector2f({start.get_x(), start.get_y()});
        dst_axis[0].color = sf::Color::Black;
        dst_axis[1].position = sf::Vector2f({end.get_x(), end.get_y()});
        dst_axis[1].color = sf::Color::Black;
    }

    void draw_axes(sf::RenderWindow &window) {
        geom_vector2 axes_center(frame_left + center);

        geom_vector2 y_axis_start(axes_center.get_x(), frame_right.get_y());
        geom_vector2 y_axis_end(axes_center.get_x(), frame_left.get_y());
        geom_vector2 x_axis_start(frame_left.get_x(), axes_center.get_y());
        geom_vector2 x_axis_end(frame_right.get_x(), axes_center.get_y());

        sf::VertexArray y_axis(sf::PrimitiveType::Lines, 2);
        sf::VertexArray x_axis(sf::PrimitiveType::Lines, 2);
        make_axis(y_axis, y_axis_start, y_axis_end); 
        make_axis(x_axis, x_axis_start, x_axis_end); 

        window.draw(y_axis);
        window.draw(x_axis);
    }
public:
    coordinate_system
    (
        const geom_vector2 &frame_left,
        const geom_vector2 &frame_right,
        const geom_vector2 &center,
        const float scale
    ): 
        frame_left(frame_left),
        frame_right(frame_right),
        center(center),
        scale(scale) 
    {   
        width = frame_right.get_x() - frame_left.get_x();
        height = frame_right.get_y() - frame_left.get_y();
        this->center += frame_left;          
    }

    void draw_plot(sf::RenderWindow &window) {
        sf::RectangleShape frame({float(width), float(height)});
        frame.setPosition({frame_left.get_x(), frame_left.get_y()});
        frame.setFillColor(sf::Color::White);
        
        window.draw(frame);
        draw_axes(window);

        // window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    }

                      

    void draw_line() {
        // cords transfrom
        
        // cs draw
        // children draw
    }

    void draw_dot() {
        // аналогично
    }


};





int main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Plots");
    coordinate_system cordsys_big({10.0, 10.0}, {300.0, 300.0}, {20.0, 20.0}, 100.0);

    // PlotWidget *big_plot = new PlotWidget(&window, {50, 50}, {550, 550}, {50, 50}, 10);
    // PlotWidget *small_plot = new PlotWidget(&window, {600, 400}, {750, 550}, {50, 50}, 10);


    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        cordsys_big.draw_plot(window);















        
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
