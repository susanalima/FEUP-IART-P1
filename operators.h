#pragma once
#include "node.h"

typedef int (*cost_function)(const node& a);
typedef node (*operators)(node a, cost_function foo);

node roll_up(node state, cost_function cost);

node roll_down(node state, cost_function cost);

node roll_left(node state, cost_function cost);

node roll_right(node state, cost_function cost);

node sideways_up(node& state, const cost_function cost, const int x1, const int y1, const int x2, const int y2);
node forewards_up(node& state, const cost_function cost, const int x1, const int y1, const int x2, const int y2, const int min_y);
node standing_up(node& state, const cost_function cost, const int x, const int y);

node sideways_down(node& state, const cost_function cost, const int x1, const int y1, const int x2, const int y2);
node forewards_down(node& state, const cost_function cost, const int x1, const int y1, const int x2, const int y2, const int min_y);
node standing_down(node& state, const cost_function cost, const int x, const int y);
