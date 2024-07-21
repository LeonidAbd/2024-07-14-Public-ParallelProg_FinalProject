#include "system.h"

System::System(double G, double delta_time, vector<Body> bodies) {
    this->G = G;
    this->delta_time = delta_time;
    this->bodies = bodies;
}
void System::move() {
    for (Body body : this->bodies) {
        body.update_acceleration(bodies, this->delta_time, this->G);
    }
    for (Body body : this->bodies) {
        body.update_coordinate_next(this->delta_time);
    }
    for (Body body : this->bodies) {
        body.update_acceleration_next(bodies, this->delta_time, this->G);
    }
    for (Body body : this->bodies) {
        body.update_velocity_next(this->delta_time);
        body.move();
    }

}
vector<Body> System::get_bodies() {
    return this->bodies;
}
