#include <iostream>
#include <vector>
#include "graphics.h"
#include "body.h"

using namespace std;

int main(void) {
    vector<Body> bodies(0);
    Body body1(1000000.0, 400, 400, 0, 0);
    body1.set_size(5);
    bodies.push_back(body1);
    Body body2(10000.0, 360, 400, 0, 100);
    bodies.push_back(body2);
    Body body3(10000.0, 470, 400, 0, -100);
    bodies.push_back(body3);
    Body body4(10000.0, 400, 510, 100, 0);
    bodies.push_back(body4);
    Body body5(10000.0, 400, 280, -100, 0);
    bodies.push_back(body5);
    Graphics instance = *Graphics::get_instance(1.0, bodies);
    instance.mainloop();
    return 0;
}