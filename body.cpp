#include <cmath>
#include "body.h"

int Body::auto_increment = 0;

Body::Body()
{
    this->id = Body::auto_increment++;
    this->size = 2;
    this->mass = 1.0;
    this->coordinate[0] = 0.0;
    this->coordinate[1] = 0.0;
    this->velocity[0] = 0;
    this->velocity[1] = 0;
    this->acceleration[0] = 0;
    this->acceleration[1] = 0;
    this->coordinate_next[0] = 0;
    this->coordinate_next[1] = 0;
    this->velocity_next[0] = 0;
    this->velocity_next[1] = 0;
    this->acceleration_next[0] = 0;
    this->acceleration_next[1] = 0;
}

Body::Body(double mass, double coordinate_x, double coordinate_y) : Body()
{
    this->mass = mass;
    this->coordinate[0] = coordinate_x;
    this->coordinate[1] = coordinate_y;
}

Body::Body(double mass, double coordinate[2]) : Body()
{
    this->mass = mass;
    this->coordinate[0] = coordinate[0];
    this->coordinate[1] = coordinate[1];
}

Body::Body(double mass, double coordinate_x, double coordinate_y, double velocity_x, double velocity_y) : Body()
{
    this->mass = mass;
    this->coordinate[0] = coordinate_x;
    this->coordinate[1] = coordinate_y;
    this->velocity[0] = velocity_x;
    this->velocity[1] = velocity_y;
}

Body::Body(double mass, double coordinate[2], double velocity[2]) : Body()
{
    this->mass = mass;
    this->coordinate[0] = coordinate[0];
    this->coordinate[1] = coordinate[1];
    this->velocity[0] = velocity[0];
    this->velocity[1] = velocity[1];
}

void Body::update_acceleration(vector<Body> bodies, double delta_t, double G)
{
    // if the acceleration is initialized already, you don't have to run this function
    for (int i = 0; i < 2; i++)
    {
        this->acceleration[i] = 0;
        for (Body body : bodies)
        {
            if (body.id == this->id)
                continue; // the body does not have a force on itself
            double r_i = pythagoras(body.coordinate, this->coordinate);
            this->acceleration[i] += G * body.mass *
                                     (body.coordinate[i] - this->coordinate[i]) / r_i / r_i / r_i; // F = G * M * m / |r|^3 * r // a
        }
    }
}

void Body::update_coordinate_next(double delta_t)
{
    for (int i = 0; i < 2; i++)
    {
        // x[t+dt] = x[t] + dt*v(t) + dt^2*a(t)/2
        this->coordinate_next[i] =
            this->coordinate[i] +
            delta_t * this->velocity[i] +
            delta_t * delta_t * 0.5 * this->acceleration[i];
    }
}

void Body::update_acceleration_next(vector<Body> bodies, double delta_t, double G)
{
    for (int i = 0; i < 2; i++)
    {
        this->acceleration_next[i] = 0;
        for (Body body : bodies)
        {
            if (body.id == this->id)
                continue; // the body does not have a force on itself
            double r_i = pythagoras(body.coordinate_next, this->coordinate_next);
            this->acceleration_next[i] += G * body.mass *
                                          (body.coordinate_next[i] - this->coordinate_next[i]) / r_i / r_i / r_i; // F = G * M * m / |r|^3 * r // a
        }
    }
}

double Body::pythagoras(double *dot1, double *dot2)
{
    double r1 = dot1[0] - dot2[0];
    double r2 = dot1[1] - dot2[1];
    return sqrt(r1 * r1 + r2 * r2);
}

void Body::update_velocity_next(double delta_t)
{
    // v[t+dt] = v[t] + dt * (a[t] + a[t+dt]/2
    for (int i = 0; i < 2; i++)
    {
        this->velocity_next[i] =
            this->velocity[i] +
            (this->acceleration[i] + this->acceleration_next[i]) * 0.5 * delta_t;
    }
}

void Body::move()
{
    for (int i = 0; i < 2; i++)
    {
        this->coordinate[i] = this->coordinate_next[i];
        this->velocity[i] = this->velocity_next[i];
        this->acceleration[i] = this->acceleration_next[i];
    }
}

double *Body::get_coordinates()
{
    return this->coordinate;
}

double Body::get_size()
{
    return this->size;
}

void Body::set_size(double size)
{
    this->size = size;
}
