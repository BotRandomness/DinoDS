#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "raylib.h"

void ground(double *scrollSpeed, double *floorX1, double *floorX2, double *floorX3, Texture2D *g1, Texture2D *g2, Texture2D *g3) 
{   
    if(*floorX1 <= -256) 
    {
        *floorX1 = 512;
    }
    else 
    {
        *floorX1 -= *scrollSpeed;
    }
    
    if (*floorX2 <= -256) 
    {
        *floorX2 = 512;
    }
    else 
    {
        *floorX2 -= *scrollSpeed;
    }
    
    if(*floorX3 <= -256) 
    {
        *floorX3 = 512;
    }
    else 
    {
        *floorX3 -= *scrollSpeed;
    }
    
    DrawTexture(*g1, *floorX1, 178, WHITE);
    DrawTexture(*g1, *floorX1+64, 178, WHITE);
    DrawTexture(*g1, *floorX1+128, 178, WHITE);
    DrawTexture(*g1, *floorX1+192, 178, WHITE);
    
    DrawTexture(*g2, *floorX2, 178, WHITE);
    DrawTexture(*g1, *floorX2+64, 178, WHITE);
    DrawTexture(*g1, *floorX2+128, 178, WHITE);
    DrawTexture(*g1, *floorX2+192, 178, WHITE);
    
    DrawTexture(*g3, *floorX3, 178, WHITE);
    DrawTexture(*g1, *floorX3+64, 178, WHITE);
    DrawTexture(*g1, *floorX3+128, 178, WHITE);
    DrawTexture(*g1, *floorX3+192, 178, WHITE);
    
    //DrawRectangle(*floorX1, 178, 256, 14, BLUE);
    //DrawTexture(*g1, *floorX1, 178, WHITE);
    
    //DrawRectangle(*floorX2, 178, 256, 14, GREEN);
    //DrawTexture(*g2, *floorX2, 178, WHITE);
    
    //DrawRectangle(*floorX3, 178, 256, 14, VIOLET);
    //DrawTexture(*g3, *floorX3, 178, WHITE);
}

void cloudAnim(double *clX1, double *clX2, double *clX3, double *cloudSpeed, Texture2D *cloud) 
{
    if(*clX1 <= -32) 
    {
        *clX1 = 256;
    }
    else 
    {
        *clX1 -= *cloudSpeed;
    }
    
    if (*clX2 <= -32) 
    {
        *clX2 = 256;
    }
    else 
    {
        *clX2 -= *cloudSpeed;
    }
    
    if(*clX3 <= -32) 
    {
        *clX3 = 256;
    }
    else 
    {
        *clX3 -= *cloudSpeed;
    }
    
    DrawTexture(*cloud, *clX1, 90, WHITE);
    DrawTexture(*cloud, *clX2, 45, WHITE);
    DrawTexture(*cloud, *clX3, 60, WHITE);
}

void obstacle(double *scrollSpeed, double *obX1, double *obX2, double *obX3, double *obX4, double *obW, double *obL, double *obY, int *randNumObs, int *randNumObs2, int *randNumObs3, int *randNumObs4, Texture2D *catus)
{   
    if(*obX1 <= -*randNumObs) 
    {
        *randNumObs = rand()%256;
        *obX1 = (*randNumObs) + 256;
        
    }
    else 
    {
        *obX1 -= *scrollSpeed;
    }
    
    if(*obX2 <= -*randNumObs2) 
    {
        *randNumObs2 = rand()%137 + 60;
        *obX2 = (*randNumObs2) + 256;
    }
    else 
    {
        *obX2 -= *scrollSpeed;
    }
    
    if(*obX3 <= -*randNumObs3) 
    {
        *randNumObs3 = rand()%216 + 20;
        *obX3 = (*randNumObs3) + 256;
    }
    else 
    {
        *obX3 -= *scrollSpeed;
    }
    
    if(*obX4 <= -*randNumObs4) 
    {
        *randNumObs4 = rand()%256;
        *obX4 = (*randNumObs4) + 256;
    }
    else 
    {
        *obX4 -= *scrollSpeed;
    }
    
    //DrawRectangle(*obX1, *obY, *obW, *obL, BLACK);
    DrawTexture(*catus, *obX1-1, *obY - 2, WHITE);
    
    //DrawRectangle(*obX2, *obY, *obW, *obL, PINK);
    DrawTexture(*catus, *obX2-1, *obY - 2, WHITE);
    
    //DrawRectangle(*obX3, *obY, *obW, *obL, GOLD);
    DrawTexture(*catus, *obX3-1, *obY - 2, WHITE);
    
    //DrawRectangle(*obX4, *obY, *obW, *obL, MAROON);
    DrawTexture(*catus, *obX4-1, *obY - 2, WHITE);
    
    //DrawRectangle(randomX, 166, 8, 16, BLACK);
    //DrawRectangle(randomX1, 166, 8, 16, BLACK);
}

bool collision(double *posX, double *posY, double *width, double *length, double *obX1, double *obX2, double *obX3, double *obX4, double *obY, double *obW, double *obL) 
{
    if (*posX < *obX1 && (*posX + *width) > *obX1 && (*posY + (*length/2.0)) > *obY) 
    {
       return true;
    }
    
    if (*posX < *obX2 && (*posX + *width) > *obX2 && (*posY + (*length/2.0)) > *obY) 
    {
        return true;
    }
    
    if (*posX < *obX3 && (*posX + *width) > *obX3 && (*posY + (*length/2.0)) > *obY) 
    {
        return true;
    }
    
    if (*posX < *obX4 && (*posX + *width) > *obX4 && (*posY + (*length/2.0)) > *obY) 
    {
        return true;
    }
    
    return false;
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 256;
    const int screenHeight = 192;

    InitWindow(screenWidth, screenHeight, "Dino");
    InitAudioDevice();
    
    Image logo = LoadImage("res/icon.png");
    SetWindowIcon(logo);
    
    double gravity = 0.99;
    double posY = 0;
    double posX = 8.3;
    double length = 16;
    double width = 16;
    double velocityY = 0;
    double jumpForce = 14.2;
    double deltaTime;
    bool onGround = false;
    
    double scrollSpeed = 3.3;
    double floorX1 = 1;
    double floorX2 = 256;
    double floorX3 = 512;
    
    double cloudSpeed = 2.2;
    double clX1 = 30;
    double clX2 = 113;
    double clX3 = 215;
    
    double obX1 = 256;
    double obX2 = 400;
    double obX3 = 600;
    double obX4 = 800;
    double obY = 158;
    double obL = 24;
    double obW = 8;
    int randNumObs = 0;
    int randNumObs2 = 0;
    int randNumObs3 = 0;
    int randNumObs4 = 0;
    
    Texture2D dino = LoadTexture("res/dino.png");
    Texture2D catus = LoadTexture("res/catus.png");
    Texture2D g1 = LoadTexture("res/1.png");
    Texture2D g2 = LoadTexture("res/2.png");
    Texture2D g3 = LoadTexture("res/3.png");
    Texture2D cloud = LoadTexture("res/clo.png");
    
    Texture2D spriteSheet = LoadTexture("res/dino_anim.png");
    int frameWidth = 32;
    int frameHeight = 32;
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 6;
    
    Texture2D titleScreen = LoadTexture("res/TitleScreen.png");
    Texture2D splashScreen = LoadTexture("res/splash.png");
    
    double score = 0;
    double currentScore = 0;
    double highScore = 0;
    
    Sound jump = LoadSound("res/jump.wav");
    Sound die = LoadSound("res/die.wav");
    Sound point = LoadSound("res/point.wav");
    
    int startTime = 0;
    
    int gameState = 2;
    
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        deltaTime = GetFrameTime()*GetFPS();
        
        if (gameState == 1) 
        {
            score += 0.2;
        
            if ((int)(score) == 100) 
            {
                scrollSpeed = 3.7;
            }
            if ((int)(score) == 530) 
            {
                scrollSpeed = 4.0;
            }
            if ((int)(score) == 1030) 
            {
                scrollSpeed = 4.4;
            }
            
            if(((int)(score)) % 100 == 0 && ((int)(score) != 0)) 
            {
                PlaySound(point);
            }
        }
        else if (gameState == 0) 
        {
            if (GetKeyPressed() != 0) 
            {
                gameState = 1;
            }
        }
        else if (gameState == 2) 
        {
            startTime++;
            
            if (startTime > 100) 
            {
                gameState = 0;
            }
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(WHITE);
            
            if (gameState == 1) 
            {
                //DrawText("LET'S GOOO", 35, 70, 30, LIGHTGRAY);
            
                //DrawText(TextFormat("%d",onGround), 35, 70, 30, LIGHTGRAY);
                
                DrawText(TextFormat("%d",(int)(score)), 0, 0, 30, LIGHTGRAY);
                
                if (onGround == false) 
                {
                    velocityY += gravity;
                    posY += (velocityY * deltaTime);
                }
                
                if (onGround == true) 
                {
                    if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_SPACE))
                    {
                        velocityY += -jumpForce;
                        posY += (velocityY * deltaTime);
                        PlaySound(jump);
                    }
                }
                
                if (posY >= 166) 
                {
                    posY = 166;
                    velocityY = 0;
                    onGround = true;
                }
                else 
                {
                    onGround = false;
                }
                
                ground(&scrollSpeed, &floorX1, &floorX2, &floorX3, &g1, &g2, &g3);
                cloudAnim(&clX1, &clX2, &clX3, &cloudSpeed, &cloud);
                
                obstacle(&scrollSpeed, &obX1, &obX2, &obX3, &obX4,&obW, &obL, &obY, &randNumObs, &randNumObs2, &randNumObs3, &randNumObs4, &catus);
                if(collision(&posX, &posY, &width, &length, &obX1, &obX2, &obX3, &obX4, &obY, &obW, &obL) == true) 
                {
                    scrollSpeed = 3.3;
                    floorX1 = 1;
                    floorX2 = 256;
                    floorX3 = 512;
                    
                    cloudSpeed = 2.2;
                    clX1 = 30;
                    clX2 = 113;
                    clX3 = 215;
                    
                    obX1 = 256;
                    obX2 = 400;
                    obX3 = 600;
                    obX4 = 800;
                    obY = 158;
                    obL = 24;
                    obW = 8;
                    randNumObs = 0;
                    randNumObs2 = 0;
                    randNumObs3 = 0;
                    randNumObs4 = 0;
                    
                    currentScore = score;
                    if (score > highScore) 
                    {
                        highScore = score;
                    }
                    score = 0;
                    
                    PlaySound(die);
                    
                    gameState = 0;
                }
            
                //DrawRectangle(posX, posY, width, length, BLACK);
            
                if(onGround) 
                {
                    framesCounter++;

                    if(framesCounter >= framesSpeed)
                    {
                        framesCounter = 0;
                        currentFrame++;

                        if(currentFrame >= 2)
                        {
                            currentFrame = 0;
                        }
                    }
                    
                    Rectangle src = {0,currentFrame*frameHeight-1,frameWidth,frameHeight};
                    Rectangle dist = {posX-3,posY-12,frameWidth,frameHeight};
                    Vector2 vec = {0,0};
                    
                    DrawTexturePro(
                        spriteSheet,
                        src,
                        dist,
                        vec,
                        0,
                        WHITE
                    );
                    
                }
                else 
                {
                    DrawTexture(dino, posX - 3, posY - 12, WHITE);
                }
            }
            else if (gameState == 0) 
            {
                DrawTexture(titleScreen, 0, 0, WHITE);
                
                if(currentScore > 1) 
                {
                    DrawText(TextFormat("%d",(int)(currentScore)), 0, 0, 10, LIGHTGRAY);
                    DrawText(TextFormat("High Score: %d",(int)(highScore)), 0, 10, 10, LIGHTGRAY);
                }
            }
            else if (gameState == 2) 
            {
                DrawTexture(splashScreen, 0, 0, WHITE);
            }
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadSound(jump);
    UnloadSound(die);
    UnloadSound(point);
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}