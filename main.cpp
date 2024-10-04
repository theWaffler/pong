#include <iostream>
#include <raylib.h>

class Ball {
    public:
        float x, y;
        int speed_x, speed_y;
        int radius;

        void Draw() {
            //drawing circle
            DrawCircle(x,y,radius,WHITE);
        }

        void Update() {
            x += speed_x;
            y += speed_y;
            if (y+radius>=GetScreenHeight() || y-radius<=0) {
                speed_y *= -1;
            }
            if (x+radius >= GetScreenWidth() || x- radius <= 0){
                speed_x *= -1;
            }
        }
};

class Paddle {
    protected:
        void limitMovement() {
            if (y <= 0) {
                y = 0;
            }
            if (y + height >= GetScreenHeight()) {
                y = GetScreenHeight() - height;
            }
        }
    public:
        float x,y;
        float width, height;
        int speed;

        void Draw(){
            DrawRectangle(x,y,width,height, WHITE);
        }

        void Update() {
            if(IsKeyDown(KEY_W)){
                y = y - speed;
            }
            if(IsKeyDown(KEY_S)) {
                y = y + speed;
            }
            limitMovement();
        }
};

class CPUPaddle : public Paddle {
    public:
        void Update(int ball_y) {
            if(y + height/2 > ball_y){
                y = y - speed;
            }
            if (y + height/2 <= ball_y) {
                y = y + speed;
            }
            limitMovement();
        }
};

Ball ball;
Paddle player;
CPUPaddle ai;

int main() {
    const int screen_width = 1280;
    const int screen_height = 800;
    //paddle
    int rec_y_pos =(screen_height/2)-(120/2);
    int radius = 10;

    //initialize window
    InitWindow(screen_width, screen_height, "Title, bitch");
    SetTargetFPS(60); // fps duh

    // ball stuff
    ball.radius = 20;
    ball.x = screen_width/2; //ignore float/int warning lol
    ball.y = screen_height/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    //player paddle
    player.height = 120;
    player.width = 25;
    player.speed = 6;
    player.x = screen_width - player.width -10;
    player.y= screen_height/2 - player.height/2;

    //ai paddle
    ai.height = 120;
    ai.width = 25;
    ai.speed = 6;
    ai.x = 10;
    ai.y = screen_height/2 - ai.height/2;

    while(WindowShouldClose() == false) {
        BeginDrawing();

        //update
        ball.Update();
        player.Update();
        ai.Update(ball.y);

        //check for collison
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{ai.x, ai.y, ai.width, ai.height})) {
            ball.speed_x *= -1;
        }

        //clears screen
        ClearBackground(BLACK);

        //draw
        DrawLine(screen_width/2,0,screen_width/2, screen_height, WHITE);
        ball.Draw();
        ai.Draw();
        player.Draw();

        EndDrawing();

    }
    // close window
    CloseWindow();

    return 0;
}
