#include "system.h"

System::System(double G, double delta_time, vector<Body> bodies) {
    this->G = G;
    this->delta_time = delta_time;
    this->bodies = bodies;
}
void System::move() {
    // ...
}
vector<Body> System::get_bodies() {
    return this->bodies;
}