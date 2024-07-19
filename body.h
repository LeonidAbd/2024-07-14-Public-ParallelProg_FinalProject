#pragma once
#include <vector>

using namespace std;

class Body {
private:
    double mass;
    double coordinate[2];
    double coordinate_next[2];
    double velocity[2];
    double velocity_next[2];
    double acceleration[2];
    double acceleration_next[2];
public:
    Body(double mass, double coordinate[2]);
    Body(double mass, double coordinate[2], double velocity[2]);
    void update_acceleration(vector<Body> bodies, double delta_t, double G);
    double pythagoras(double* dot1, double* dot2);
    void update_coordinate_next(double delta_t);
    void update_acceleration_next(vector<Body> bodies, double delta_t, double G);
    void update_velocity_next(double delta_t);
    void move();
    double* getCoords();
};
