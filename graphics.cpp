#include "graphics.h"

#include <string>
#include <sstream>

using namespace std;

Graphics *Graphics::instance = nullptr;

Graphics::Graphics() : system(), bodies_settings() {}

Graphics::Graphics(double G, vector<Body> bodies) : system(G, 1.0 / 32.0, bodies), bodies_settings() {}

Graphics::Graphics(double G, double delta_t, vector<Body> bodies) : system(G, delta_t, bodies), bodies_settings() {}

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

Graphics *Graphics::get_instance(double G, double delta_t, vector<Body> bodies)
{
    if (Graphics::instance == nullptr)
        Graphics::instance = new Graphics(G, delta_t, bodies);
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
        string str = (stringstream("") << "time: sec " << this->system.get_time()).str();
        DrawText(str.c_str(), 10, 10, 20, WHITE);
        // DrawCircle(100, 100, 2, WHITE);
        for (vector<int> settings : this->bodies_settings)
            DrawCircle(settings[0], settings[1], settings[2], WHITE);
        EndDrawing();
        this->system.move();
    }
    CloseWindow();
}

void Graphics::update_bodies_settings()
{
    vector<vector<int>> coordinates_list_upcoming(0);
    for (Body body : this->system.get_bodies())
    {
        vector<int> coordinates(0);
        double *result = body.get_coordinates();
        coordinates.push_back(round(result[0]));
        coordinates.push_back(round(result[1]));
        coordinates.push_back(body.get_size());
        coordinates_list_upcoming.push_back(coordinates);
    }
    this->bodies_settings = coordinates_list_upcoming;
}