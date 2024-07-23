#pragma once
#include <raylib.h>
#include "system.h"
#include "body_settings.cpp"

class Graphics {
private:
    static Graphics* instance;
    int frame_rate = 32;
    System system;
    vector<Body_Setting> bodies_settings;
    double frames_time = 0;
    Graphics();
    Graphics(double G, vector<Body> bodies);
    Graphics(double G, vector<Body> bodies, int frame_rate);
    Graphics(double G, vector<Body> bodies, int frame_rate, double delta_time);
public:
    static Graphics* get_instance();
    static Graphics* get_instance(double G, vector<Body> bodies);
    static Graphics* get_instance(double G, vector<Body> bodies, int frame_rate);
    static Graphics* get_instance(double G, vector<Body> bodies, int frame_rate, double delta_time);
    void mainloop();
    void draw_text();
    void update_bodies_settings();
};
