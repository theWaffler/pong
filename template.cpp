#include <iostream>
#include <raylib.h>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    int ball_x = screenWidth/2; // x-coordinate
    int ball_y = screenHeight/2; // y-coordinate
    int ball_speed_x = 5; //speed for left and right
    int ball_speed_y = 5; //speed for up and down
    int ball_radius = 15; // size of balls

    std::cout << "Hello bitches!" << std::endl;

    InitWindow(screenWidth, screenHeight, "screen vcard taken!");
    SetTargetFPS(60); // target 60fps

    while(WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(BLACK);
        ball_x += ball_speed_x;
        ball_y += ball_speed_y;

        if (ball_x + ball_radius >= screenWidth || ball_x - ball_radius <= 0) {
            ball_speed_x *= -1;
        }

        if (ball_y + ball_radius >= screenHeight || ball_y - ball_radius <= 0) {
            ball_speed_y *=-1;
        }
        DrawCircle(ball_x,ball_y,ball_radius, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
