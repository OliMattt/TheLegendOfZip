/*******************************************************************************************
*
*   Trabalho de LAB AED-1
*
*   Nomes:  Giulia Ramos Bagodi
*           Mateus Pereira de Oliveira
*           Yuri Soinaktvitz Stockler
*
********************************************************************************************/
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

#define zip_width           384
#define zip_height          128 

#define ZIPBLUE             (Color){108,185,201,255}

// Funções de movimento dos personagens
void movInim(void);

// struct Vector2 possui a posição X e Y da imagem

float enemyX = 200;
float enemyY = 200;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitAudioDevice();
    InitWindow(screenWidth, screenHeight, "A Lenda de Zip");

// Define o Pause
    bool Paused = false;

    Texture2D background = LoadTexture("resources/mapa1.png");
    Texture2D zip = LoadTexture("resources/zip11.png");        // Texture loading
    Texture2D up = LoadTexture("resources/up.png");
    Texture2D down = LoadTexture("resources/down.png");
    Texture2D left = LoadTexture("resources/left.png");
    Texture2D right = LoadTexture("resources/right.png");

//Inicia o mapa na posiçao 0.0 e define sua velocidade
    Vector2 mapPos={0.0, 0.0};
    float speed = 5.0;
    
// Vetor de posição do gato
    Vector2 zipPos = {
        (float)screenWidth/2.0f - 4.0f * (0.5f * (float)zip_width/7.0f),
        (float)screenHeight/2.0f - 4.0f * (0.5f * (float)zip_height)
    };

// Vetor de posição da animação parada
// Retângulo que delimita o frame apresentado
// Inicia no frame 0
    Vector2 position = { 350.0f, 280.0f };
    Rectangle frameRec = { 0.0f, 0.0f, (float)zip_width/6, (float)zip_height };
    int currentFrame = 0;


// Contador e Velocidade de frame (por segundo)
    int framesCounter = 0;
    int framesSpeed = 8;            // Number of spritesheet frames shown by second

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    //Enquanto a janela de jogo não fechar, o código não é executado
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        if(IsKeyPressed(KEY_SPACE))
            Paused = !Paused;

    if (!Paused)
    {
    
        framesCounter++;

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = (float)currentFrame*(float)zip_width/6;
        }

        
        //----------------------------------------------------------------------------------
    }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // Desenha o mapa ==> imagem, posição na tela, rotação, tamanho, cor da imagem
            ClearBackground(ZIPBLUE);

             // Desenha o mapa
            DrawTextureEx(background, mapPos, 0.0, 4.0, WHITE);
            
        Rectangle source = {0.f, 0.f, (float)zip_width/6.f, (float)zip_height};
        Rectangle dest = {zipPos.x, zipPos.y, 4.0f * (float)zip_width/6.0f, 4.0f * (float)zip_height};
        Vector2 origin = {};

        Vector2 direction = {};
            if (IsKeyDown(KEY_A)){   
                direction.x -= 1.0;
               
                DrawTextureRec(left, frameRec, position, WHITE);  // Draw part of the texture
            }   
            if (IsKeyDown(KEY_D)){
                direction.x += 1.0;
                DrawTextureRec(right, frameRec, position, WHITE);  // Draw part of the texture
            }
            if (IsKeyDown(KEY_W)){
                direction.y -= 1.0;
                DrawTextureRec(up, frameRec, position, WHITE);  // Draw part of the texture
            }  
            if (IsKeyDown(KEY_S)){   
                direction.y += 1.0;
                DrawTextureRec(down, frameRec, position, WHITE);  // Draw part of the texture
            }
            if (Vector2Length(direction) != 0.0)
        {
            // set mapPod = mapPos - direction
            
            //Vector 2 pega o valor de um vetor e normaliza para 1
            //Impede que o gato ande mais rapido na diagonal
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction),speed));
        }
            else{
                DrawTextureRec(zip, frameRec, position, WHITE);  // Draw part of the texture

            }

           
            
            // Desenha parte das texturas do gato e o centraliza na tela
            

            if (Paused)
                DrawText("Paused", 600, 380, 40, GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(zip);       // Texture unloading
    UnloadTexture(up);
    UnloadTexture(down);
    UnloadTexture(right);
    UnloadTexture(left);
    //UnloadTexture(background);


    CloseAudioDevice();
    
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
