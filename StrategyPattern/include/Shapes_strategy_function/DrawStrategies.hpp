#pragma once

#include <Shapes_strategy_function/Circle.hpp>
#include <Shapes_strategy_function/Rectangle.hpp>
#include <Shapes_strategy_function/Triangle.hpp>

namespace shapes_strategy_function {

void draw_circle_with_stars(Circle const& circle);
void draw_rectangle_with_stars(Rectangle const& rectangle);
void draw_triangle_with_stars(Triangle const& triangle);

void send_circle_to_api(Circle const& circle);
void send_rectangle_to_api(Rectangle const& rectangle);
void send_triangle_to_api(Triangle const& triangle);

}  // namespace shapes_strategy_function
