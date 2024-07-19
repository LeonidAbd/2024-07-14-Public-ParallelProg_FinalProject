#include <cmath>
#include "body.h"

Body::Body(double mass, double coordinate[2]) {
    this->mass = mass;
    this->coordinate[0] = coordinate[0];
    this->coordinate[1] = coordinate[1];
    this->velocity[0] = 0;
    this->velocity[1] = 0;
    this->acceleration[0] = NULL;
    this->acceleration[1] = NULL;
    this->coordinate_next[0] = NULL;
    this->coordinate_next[1] = NULL;
    this->velocity_next[0] = NULL;
    this->velocity_next[1] = NULL;
    this->acceleration_next[0] = NULL;
    this->acceleration_next[1] = NULL;
}

Body::Body(double mass, double coordinate[2], double velocity[2]) {
    this->mass = mass;
    this->coordinate[0] = coordinate[0];
    this->coordinate[1] = coordinate[1];
    this->velocity[0] = velocity[0];
    this->velocity[1] = velocity[1];
    this->acceleration[0] = NULL;
    this->acceleration[1] = NULL;
    this->coordinate_next[0] = NULL;
    this->coordinate_next[1] = NULL;
    this->velocity_next[0] = NULL;
    this->velocity_next[1] = NULL;
    this->acceleration_next[0] = NULL;
    this->acceleration_next[1] = NULL;
}

void Body::update_acceleration(vector<Body> bodies, double delta_t, double G) {
    if (this->acceleration_next != NULL)
        return;  // which means that after the move A = A_next. The method is going to be used to initialize the acceleration anyway.
    for (int i = 0; i < 2; i++) {
        this->acceleration[i] = 0;
        for (Body body : bodies) {
            if (&body == this) continue;  // the body does not have a force on itself
            double r_i = pythagoras(body.coordinate, this->coordinate);
            this->acceleration[i] += G * body.mass / r_i / abs(r_i);
        }
    }
}

void Body::update_coordinate_next(double delta_t) {
    for (int i = 0; i < 2; i++) {
        // x[t+dt] = x[t] + dt*v(t) + dt^2*a(t)/2
        this->coordinate_next[i] =
            this->coordinate[i] +
            delta_t * this->velocity[i] +
            delta_t * delta_t * 0.5 * this->acceleration[i];
    }
}

void Body::update_acceleration_next(vector<Body> bodies, double delta_t, double G) {
    for (int i = 0; i < 2; i++) {
        this->acceleration_next[i] = 0;
        for (Body body : bodies) {
            if (&body == this) continue;  // the body does not have a force on itself
            double r_i = pythagoras(body.coordinate_next, this->coordinate_next);
            this->acceleration_next[i] += G * body.mass / r_i / abs(r_i);  // F = G * M * m / |r|^3 * r // a = G * M / |r| / r
        }
    }
}

double Body::pythagoras(double* dot1, double* dot2) {
    double r1 = dot1[0] - dot2[0];
    double r2 = dot1[1] - dot2[1];
    return sqrt(r1 * r1 + r2 * r2);
}

void Body::update_velocity_next(double delta_t) {
    // v[t+dt] = v[t] + dt * (a[t] + a[t+dt]/2
    for (int i = 0; i < 2; i++) {
        this->velocity_next[i] =
            this->velocity[i] + 
            (this->acceleration[i] + this->acceleration_next[i]) * 0.5 * delta_t;
    }
}

void Body::move() {
    for (int i = 0; i < 2; i++) {
        this->coordinate[i] = this->coordinate_next[i];
        this->velocity[i] = this->velocity_next[i];
        this->acceleration[i] = this->acceleration_next[i];
    }
}

double* Body::getCoords() {
    return this->coordinate;
}
