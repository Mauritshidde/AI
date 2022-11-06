#include <raylib.h>
#include <iostream>

const int screenWidth = 1400;
const int screenHeight = 600;

bool server = false;


struct Player {
    Vector2 position;
    const Vector2 size{10, 20};
    const float speed = 300.0f; //speed of the paddle.

    int score = 0;

    float bounceAddForce = 150; //how much extra speed is added to the current x speed of the ball.
    float bounceMultiply = 700; //how much the angle of the ball changes after the bounce of the paddle.
    float bounceBallInfluence = 0.5; //0.0f-1.0f range recomended. Influence of the current speed on the speed following the bounce.

    void Draw(){
        DrawRectangle(position.x-size.x/2, position.y-size.y/2, size.x, size.y, WHITE);
    }

    Rectangle getRec(){
        return Rectangle{position.x-size.x/2, position.y-size.y/2, size.x, size.y};
    }
};

struct Ball {
    Vector2 position;
    Vector2 speed;

    const float radius = 10;

    void Draw(){
        DrawCircle(position.x, position.y, radius, WHITE);
    }
};

Player leftPaddle;
Player rightPaddle;

Ball ball;

const char* winnerText = nullptr;

void Start(){
    leftPaddle.position = {50, screenHeight/2};
    rightPaddle.position = {-50+screenWidth, screenHeight/2};
    ball.position = {screenWidth/2, screenHeight/2};
    ball.speed = {(server ? -500.0f : 500.0f), (float) GetRandomValue(-400, 400)};
}

void Update(double delta){
    if (IsKeyDown(KEY_W)){
        leftPaddle.position.y -= leftPaddle.speed * delta;
    } else if (IsKeyDown(KEY_S)){
        leftPaddle.position.y += leftPaddle.speed * delta;
    }

    if (IsKeyDown(KEY_UP)){
        leftPaddle.position.x -= rightPaddle.speed * delta;
    } else if (IsKeyDown(KEY_DOWN)){
        leftPaddle.position.x += rightPaddle.speed * delta;
    }

    if (leftPaddle.position.y-leftPaddle.size.y/2<0){
        leftPaddle.position.y=0+leftPaddle.size.y/2;
    }else if (leftPaddle.position.y+leftPaddle.size.y/2>screenHeight){
        leftPaddle.position.y = screenHeight-leftPaddle.size.y/2;
    }

    if (rightPaddle.position.y-rightPaddle.size.y/2<0){
        rightPaddle.position.y=0+rightPaddle.size.y/2;
    }else if (rightPaddle.position.y+rightPaddle.size.y/2>screenHeight){
        rightPaddle.position.y = screenHeight-rightPaddle.size.y/2;
    }

    ball.position.x += ball.speed.x * delta;
    ball.position.y += ball.speed.y * delta;

    if (ball.position.y<0+ball.radius){
        ball.position.y=0+ball.radius;
        ball.speed.y *= -1;
    } else if (ball.position.y>screenHeight-ball.radius){
        ball.position.y=screenHeight-ball.radius;
        ball.speed.y *= -1;
    }

    if (ball.position.x<0){
        if (rightPaddle.score>=10){
            rightPaddle.score = 11;
            winnerText = TextFormat("Right player is the winner!");
        } else {
            rightPaddle.score++;
            server = false;
            Start();
        }
    } else if (ball.position.x>screenWidth){
        if (leftPaddle.score>=10){
            leftPaddle.score = 11;
            winnerText = TextFormat("Left player is the winner!");
        } else {
            leftPaddle.score++;
            server = true;
            Start();
        }
    }


    if(CheckCollisionCircleRec(ball.position, ball.radius, leftPaddle.getRec())){
        if (ball.speed.x < 0){
            float difPos = (ball.position.y - leftPaddle.position.y) / (leftPaddle.size.y/2);
            ball.speed.y = ball.speed.y*leftPaddle.bounceBallInfluence + difPos*leftPaddle.bounceMultiply;

            ball.speed.x = ball.speed.x*-1+leftPaddle.bounceAddForce;
            
        }
    }else if(CheckCollisionCircleRec(ball.position, ball.radius, rightPaddle.getRec())){
        if (ball.speed.x > 0){
            float difPos = (ball.position.y - rightPaddle.position.y) / (rightPaddle.size.y/2);
            ball.speed.y = ball.speed.y*rightPaddle.bounceBallInfluence + difPos*rightPaddle.bounceMultiply;
            
            ball.speed.x = ball.speed.x*-1-rightPaddle.bounceAddForce;
        }
    }
}

void Render(){
    const Color backgroundColor = BLACK;

    BeginDrawing();
    ClearBackground(backgroundColor);
    leftPaddle.Draw();
    rightPaddle.Draw();
    ball.Draw();

    DrawLineEx({screenWidth/2, 0}, {screenWidth/2, screenHeight}, 1, WHITE);
    const char *ScoreL = TextFormat("%i", leftPaddle.score);
    const char *ScoreR = TextFormat("%i", rightPaddle.score);
    DrawText(ScoreL, -MeasureText(ScoreL, 90)/2 +screenWidth/2 - 100, 10, 90, WHITE);
    DrawText(ScoreR, -MeasureText(ScoreR, 90)/2 +screenWidth/2 + 100, 10, 90, WHITE);
    
    if(winnerText){
        DrawText(winnerText, 200, 200,60,WHITE);
    }

    EndDrawing();
}

int main(void){
    InitWindow(screenWidth, screenHeight, "Pong!");
    SetWindowState(FLAG_VSYNC_HINT);

    server = (int) GetRandomValue(0,1);
    Start();
    while (!WindowShouldClose()){
        double deltaTime = GetFrameTime();
        Update(deltaTime);
        Render();
    }

    CloseWindow();
    return 0;
}