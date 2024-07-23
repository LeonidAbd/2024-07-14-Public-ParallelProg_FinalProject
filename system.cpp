#include "system.h"

System::System() {
    this->G = 1;
    this->delta_time = 1.0 / 32.0;
    this->bodies = {};
    this->is_acceleration_initialized = false;
    this->time = 0;
}

System::System(double G, double delta_time, vector<Body> bodies) {
    this->G = G;
    this->delta_time = delta_time;
    this->bodies = bodies;
    this->is_acceleration_initialized = false;
    this->time = 0;
}
void System::move() {
    // if the acceleration is not initialized yet, we must do it here
    if (!this->is_acceleration_initialized) {
        for (int body_id = 0; body_id < this->bodies.size(); body_id++) {
            this->bodies[body_id].update_acceleration(this->bodies, this->delta_time, this->G);
            this->bodies[body_id].update_coordinate_next(this->delta_time);
        }
        this->is_acceleration_initialized = true;
    } else {
        for (int body_id = 0; body_id < this->bodies.size(); body_id++)
            this->bodies[body_id].update_coordinate_next(this->delta_time);
    }
    for (int body_id = 0; body_id < this->bodies.size(); body_id++) {
        // we have to make a new cycle, because
        // the acceleration_next needs all the bodies with updated coordinate_next
        this->bodies[body_id].update_acceleration_next(this->bodies, this->delta_time, this->G);
        this->bodies[body_id].update_velocity_next(this->delta_time);
        this->bodies[body_id].move();
    }
    this->time += this->delta_time;
}

vector<Body> System::get_bodies() {
    return this->bodies;
}

double System::get_time() {
    return this->time;
}
