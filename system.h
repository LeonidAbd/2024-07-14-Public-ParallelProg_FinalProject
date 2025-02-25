#pragma once
#include <vector>
#include "body.h"

using namespace std;

class System {
private:
    double G;  // Gravity constant
    double delta_time;
    vector<Body> bodies;  // vector = List/ArrayList
    bool is_acceleration_initialized;
    double time;
public:
    System();
    System(double G, double delta_time, vector<Body> bodies);
    void move();
    vector<Body> get_bodies();
    double get_time();
};
