// #include <visual.hpp>
// #include <stdint.h>
// #include <stdio.h>
// #include <SFML/Graphics.hpp>


// class CoordinateSystem{
// public:
//     sf::Vector2f size;
//     sf::Vector2f position;

//     float pixels_per_unit;
//     sf::Vector2f center;

//     CoordinateSystem(sf::Vector2f size,
//                      sf::Vector2f position = sf::Vector2f{0.f, 0.f},
//                      sf::Vector2f center = sf::Vector2f{0.f, 0.f},
//                      float pixels_per_unit = 50.f);

//     void drawPlot(sf::RenderWindow& window);

//     void drawFunc(sf::RenderWindow& window, float (*func)(float));

//     void drawVec(sf::RenderWindow& window, Vector dot, Vector vec);

// private:
//     sf::RectangleShape canvas;
//     sf::VertexArray y_axis;
//     sf::VertexArray x_axis;

//     float marks_eps;
//     int marks_amount;

//     void getAxes();
//     void setMarks(sf::RenderWindow& window);
//     bool isInside(sf::Vector2f dot);

//     void drawVecPrivate(sf::RenderWindow& window, Vector dot, Vector vec);
// };


// coordinate_system::coordinate_system(sf::Vector2f size,
//                                      sf::Vector2f position,
//                                      sf::Vector2f center,
//                                      float pixels_per_unit){
//     this->size = size;
//     this->position = position;
//     this->center = center;
//     this->pixels_per_unit = pixels_per_unit;

//     canvas = sf::RectangleShape(size);

//     canvas.setPosition(position);
//     canvas.setFillColor(sf::Color::White);

//     getAxes();

//     marks_eps = 10;
//     marks_amount = int(size.x) / int(pixels_per_unit);
// }

// void coordinate_system::drawPlot(sf::RenderWindow& window){
//     window.draw(canvas);

//     window.draw(x_axis);
//     window.draw(y_axis);

//     setMarks(window);
// }

// void coordinate_system::getAxes(){
//     y_axis = sf::VertexArray(sf::PrimitiveType::Lines, 2);
//     x_axis = sf::VertexArray(sf::PrimitiveType::Lines, 2);

//     sf::Vector2f plot_window_center = {position.x + size.x / 2, position.y + size.y / 2};

//     y_axis[0].position = sf::Vector2f({plot_window_center.x - int(center.x * pixels_per_unit), position.y});
//     y_axis[0].color = sf::Color::Black;
//     y_axis[1].position = sf::Vector2f({plot_window_center.x - int(center.x * pixels_per_unit), position.y + size.y});
//     y_axis[1].color = sf::Color::Black;

//     x_axis[0].position = sf::Vector2f({position.x, plot_window_center.y + int(center.y * pixels_per_unit)});
//     x_axis[0].color = sf::Color::Black;
//     x_axis[1].position = sf::Vector2f({position.x + size.x, plot_window_center.y + int(center.y * pixels_per_unit)});
//     x_axis[1].color = sf::Color::Black;
// }

// void coordinate_system::setMarks(sf::RenderWindow& window){
//     sf::VertexArray mark(sf::PrimitiveType::Lines, 2);

//     sf::Vector2f plot_window_center = {position.x + size.x / 2, position.y + size.y / 2};

//     for (int i = 0; i <= marks_amount; i++){
//         mark[0].position = sf::Vector2f({plot_window_center.x - marks_eps / 2 - int(center.x * pixels_per_unit), position.y + i * pixels_per_unit});
//         mark[0].color = sf::Color::Black;

//         mark[1].position = sf::Vector2f({plot_window_center.x + marks_eps / 2 - int(center.x * pixels_per_unit), position.y + i * pixels_per_unit});
//         mark[1].color = sf::Color::Black;

//         window.draw(mark);
//     }

//     for (int i = 0; i <= marks_amount; i++){
//         mark[0].position = sf::Vector2f({position.x + i * pixels_per_unit, plot_window_center.y + marks_eps / 2 + int(center.y * pixels_per_unit)});
//         mark[0].color = sf::Color::Black;

//         mark[1].position = sf::Vector2f({position.x + i * pixels_per_unit, plot_window_center.y - marks_eps / 2 + int(center.y * pixels_per_unit)});
//         mark[1].color = sf::Color::Black;

//         window.draw(mark);
//     }
// }

// bool coordinate_system::isInside(sf::Vector2f dot){
//     if (dot.y > center.y + size.y / pixels_per_unit / 2 ||
//         dot.y < center.y - size.y / pixels_per_unit / 2)
//         return false;

//     if (dot.x > center.x + size.x / pixels_per_unit / 2 ||
//         dot.x < center.x - size.x / pixels_per_unit / 2)
//         return false;

//     return true;
// }

// void coordinate_system::drawFunc(sf::RenderWindow& window, float (*func)(float)){
//     sf::VertexArray dot(sf::PrimitiveType::Points, 1);
//     dot[0].color = sf::Color::Black;

//     for (int x = 0; x < size.x; x++){
//         float x_plot = (x - size.x / 2) / pixels_per_unit + center.x;
//         float y_plot = func(x_plot);

//         if (!isInside({x_plot, y_plot})) continue;

//         float x_window = (x_plot - center.x) * pixels_per_unit + position.x + size.x / 2;
//         float y_window = 2 * position.y + size.y - ((y_plot - center.y) * pixels_per_unit + position.y + size.y / 2);

//         dot[0].position = {x_window, y_window};

//         window.draw(dot);
//     }
// }

// void coordinate_system::drawVecPrivate(sf::RenderWindow& window, Vector dot, Vector vec){
//     sf::VertexArray vector(sf::PrimitiveType::Lines, 2);
//     vector[0].color = sf::Color::Black;
//     vector[1].color = sf::Color::Black;

//     Vector begin_plot = {dot.x, dot.y};
//     Vector end_plot = {dot.x + vec.x, dot.y + vec.y};

//     Vector begin_window = {((begin_plot.x - center.x) * pixels_per_unit + position.x + size.x / 2),
//                            2 * position.y + size.y - ((begin_plot.y - center.y) * pixels_per_unit + position.y + size.y / 2)};
//     Vector end_window = {((end_plot.x - center.x) * pixels_per_unit + position.x + size.x / 2),
//                            2 * position.y + size.y - ((end_plot.y - center.y) * pixels_per_unit + position.y + size.y / 2)};

//     vector[0].position = {begin_window.x, begin_window.y};
//     vector[1].position = {end_window.x, end_window.y};

//     window.draw(vector);
// }

// void coordinate_system::drawVec(sf::RenderWindow& window, Vector dot, Vector vec){
//     drawVecPrivate(window, dot, vec);
//     drawVecPrivate(window, dot + vec, vec.normal().rotate(M_PI / 4) / 4);
//     drawVecPrivate(window, dot + vec, vec.normal().rotate(M_PI / 4).reflect(vec) / 4);
// }