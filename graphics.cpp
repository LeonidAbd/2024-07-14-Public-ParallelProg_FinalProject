#include "graphics.h"

#include <string>
#include <sstream>
#include <omp.h>

using namespace std;

Graphics *Graphics::instance = nullptr;

Graphics::Graphics() : system(), bodies_settings() {}

Graphics::Graphics(double G, vector<Body> bodies) : system(G, 1.0 / 32.0, bodies), bodies_settings() {}

Graphics::Graphics(double G, vector<Body> bodies, int frame_rate) : system(G, (double)1 / frame_rate, bodies), bodies_settings()
{
    this->frame_rate = frame_rate;
}
Graphics::Graphics(double G, vector<Body> bodies, int frame_rate, double delta_time) : system(G, delta_time, bodies), bodies_settings()
{
    this->frame_rate = frame_rate;
}

Graphics *Graphics::get_instance()
{
    if (Graphics::instance == nullptr)
        Graphics::instance = new Graphics();
    return Graphics::instance;
}

Graphics *Graphics::get_instance(double G, vector<Body> bodies)
{
    if (Graphics::instance == nullptr)
        Graphics::instance = new Graphics(G, bodies);
    return Graphics::instance;
}

Graphics *Graphics::get_instance(double G, vector<Body> bodies, int frame_rate)
{
    if (Graphics::instance == nullptr)
        Graphics::instance = new Graphics(G, bodies, frame_rate);
    return Graphics::instance;
}

Graphics *Graphics::get_instance(double G, vector<Body> bodies, int frame_rate, double delta_time)
{
    if (Graphics::instance == nullptr)
        Graphics::instance = new Graphics(G, bodies, frame_rate, delta_time);
    return Graphics::instance;
}

void Graphics::mainloop()
{
    const int screen_width = 800;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Graphics window");
    SetTargetFPS(32);
    while (!WindowShouldClose())
    {
        this->update_bodies_settings();
        BeginDrawing();
        ClearBackground(BLACK);
        // DrawRectangle(99, 0, 2, screen_height, CLITERAL(Color) {255, 255, 255, 64});
        // DrawRectangle(0, 99, screen_width, 2, CLITERAL(Color) {255, 255, 255, 64});

        this->draw_text();

        // DrawCircle(100, 100, 2, WHITE);
        for (int i = 0; i < this->bodies_settings.size(); i++)
            DrawCircle(this->bodies_settings[i].x, this->bodies_settings[i].y, this->bodies_settings[i].size, WHITE);
        EndDrawing();
        this->system.move();
        this->frames_time += GetFrameTime();
    }
    CloseWindow();
}

void Graphics::draw_text()
{
    string str_timer_title = "Time in system:";
    DrawText(str_timer_title.c_str(), 10, 10, 20, CLITERAL(Color){255, 255, 255, 159});

    string str_timer = (stringstream("") << this->system.get_time()).str();
    DrawText(str_timer.c_str(), 180, 10, 20, CLITERAL(Color){255, 255, 255, 159});

    string str_frametimer_title = "Time in gui:";
    DrawText(str_frametimer_title.c_str(), 10, 35, 20, CLITERAL(Color){255, 255, 255, 159});

    string str_frametimer = (stringstream("") << this->frames_time).str();
    // string str_frametimer = (stringstream("") << this->frame_count / (double)this->frame_rate).str();
    DrawText(str_frametimer.c_str(), 180, 35, 20, CLITERAL(Color){255, 255, 255, 159});

    string str_defectaspect_title = "Defect aspect:";
    DrawText(str_defectaspect_title.c_str(), 10, 60, 20, CLITERAL(Color){255, 255, 255, 159});

    string str_defectaspect = (stringstream("") << this->frames_time / this->system.get_time()).str();
    DrawText(str_defectaspect.c_str(), 180, 60, 20, CLITERAL(Color){255, 255, 255, 159});

    string str_framerate_title = "Frame rate:";
    DrawText(str_framerate_title.c_str(), 40, 90, 15, CLITERAL(Color){255, 255, 255, 159});

    string str_framerate = (stringstream("") << this->frame_rate).str();
    DrawText(str_framerate.c_str(), 170, 90, 15, CLITERAL(Color){255, 255, 255, 159});

    string str_bodycount_title = "Bodies count:";
    DrawText(str_bodycount_title.c_str(), 40, 110, 15, CLITERAL(Color){255, 255, 255, 159});

    string str_bodycount = (stringstream("") << this->bodies_settings.size()).str();
    DrawText(str_bodycount.c_str(), 170, 110, 15, CLITERAL(Color){255, 255, 255, 159});

    string str_ompthreads_title = "Threads count:";
    DrawText(str_ompthreads_title.c_str(), 40, 130, 15, CLITERAL(Color){255, 255, 255, 159});

    string str_ompthreads = (stringstream("") << omp_get_max_threads()).str();
    DrawText(str_ompthreads.c_str(), 170, 130, 15, CLITERAL(Color){255, 255, 255, 159});

    DrawFPS(710, 10);
}

void Graphics::update_bodies_settings()
{
    this->bodies_settings.clear();
    for (Body body : this->system.get_bodies())
        this->bodies_settings.push_back(Body_Setting(body.get_coordinates(), body.get_size()));
}
