#pragma once
#include <raylib.h>
#include "system.h"

class Graphics {
private:
    static Graphics* instance;
    System system;
    vector<vector<int>> bodies_settings;
    Graphics();
    Graphics(double G, vector<Body> bodies);
    Graphics(double G, double delta_t, vector<Body> bodies);
public:
    static Graphics* get_instance();
    static Graphics* get_instance(double G, vector<Body> bodies);
    static Graphics* get_instance(double G, double delta_t, vector<Body> bodies);
    void mainloop();
    void update_bodies_settings();
};
