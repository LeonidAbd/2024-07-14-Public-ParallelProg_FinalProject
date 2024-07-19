#pragma once
#include <vector>
#include "body.h"

using namespace std;

class System {
private:
    double G;  // Gravity constant
    double delta_time;
    vector<Body> bodies;  // vector = List/ArrayList
public:
    System(double G, double delta_time, vector<Body> bodies);
    void move();
    vector<Body> get_bodies();
};