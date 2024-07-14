#include "graphics.h"

Graphics* Graphics::instance = nullptr;

Graphics::Graphics() {
    
}

Graphics* Graphics::get_instance() {
    if (Graphics::instance == nullptr)
        Graphics::instance = new Graphics();
    return Graphics::instance;
}

void Graphics::mainloop() {
    const int screen_width = 800;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Graphics window");
    SetTargetFPS(40);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(99, 0, 2, screen_height, CLITERAL(Color) {255, 255, 255, 64});
        DrawRectangle(0, 99, screen_width, 2, CLITERAL(Color) {255, 255, 255, 64});
        //DrawCircle(100, 100, 2, WHITE);
        DrawCircle(100, 100, 3, WHITE);
        EndDrawing();
    }
    CloseWindow();
}