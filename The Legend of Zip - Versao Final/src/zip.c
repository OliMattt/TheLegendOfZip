/*******************************************************************************************
*
*   Trabalho de LAB AED-2 / AED-2
*
*   Nomes:  Giulia Ramos Bagodi
*           Mateus Pereira de Oliveira
*           Octavio Patrocinio
*           Yuri Soinaktvitz Stockler
*

Criação de um jogo em C utilizando a biblioteca raylib.h

    Nosso projeto constitui de um jogo de RPG 2D,
    o qual você acompanha os primórdios do surgimento do Zip,
    um gatinho aprendiz de magia (e nosso herói) que mora em um mundo de computador
    onde feitiços são dados por códigos, bugs são uma ameaça perigosa
    que tomaram conta do reino e nosso gatinho aprendiz tem que salvar o mundo.

    Este código foi feito em forma de projeto, portanto para sua execução eh necessario
    duas linhas de comando no terminal do Linux:
    
    Compila:
    gcc -Wall  src/zip.c lib/lista.c lib/draw.c lib/save.c  -o zip -lraylib
    
    
    Executa:
    ./zip

********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/zip.h"

// Definições para frames de animação
#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

// Definições do tamanho do Zip para facilitar animação
#define zip_width 384
#define zip_height 128
#define ZIPBLUE (Color) { 108, 185, 201, 255 }

// retangulos de menus
Rectangle ButtonExitYes = {244, 300, 122, 25};
Rectangle ButtonExitNo = {456, 300, 112, 25};

int main(void)
{

    // declarações para SavemGame
    SaveData gameData;
    gameData.Life = 200;
    gameData.level = 1;
    strcpy(gameData.name, "Zip");
    const char *saveFile = "savegame.dat";

    bool saveKeyPressed = false;
    bool loadKeyPressed = false;

    // tamanho da janela
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "The Legend of Zip"); //Inicia a janela
    InitAudioDevice(); //Inicia o audio

    //Declaração de audio
    Music music = LoadMusicStream("resources/Song.mp3");
    //-----------------------------------------------------------------
    // Declarações de textura
    Font fonte = LoadFont("resources/pixantiqua.png");
    Texture2D logo = LoadTexture("resources/Logo.png");
    Texture2D menu1 = LoadTexture("resources/zip.png");
    Texture2D buttonNew = LoadTexture("resources/ButtonNewGame.png");
    Texture2D buttonCred = LoadTexture("resources/ButtonCredits.png");
    Texture2D buttonExit = LoadTexture("resources/ButtonExit.png");
    Texture2D buttonYes = LoadTexture("resources/ButtonYes.png");
    Texture2D buttonNo = LoadTexture("resources/ButtonNo.png");
    Texture2D buttonBack = LoadTexture("resources/ButtonBack.png");

    Texture2D background = LoadTexture("resources/mapa1.png");
    Texture2D zip = LoadTexture("resources/zip11.png"); // Texture loading
    Texture2D up = LoadTexture("resources/up.png");
    Texture2D down = LoadTexture("resources/down.png");
    Texture2D left = LoadTexture("resources/left.png");
    Texture2D right = LoadTexture("resources/right.png"); // Texture loading
    //-----------------------------------------------------------------------

    // Declaração de retangulos dos botoes (colisao)
    Rectangle Button1 = {144, 100, 112, 25};
    Rectangle Button2 = {144, 150, 112, 25};
    Rectangle Button3 = {144, 200, 112, 25};
    Rectangle Button4 = {344, 350, 112, 25};

    //----------------------------------------------------------------------

    // check (padrao falso para verificação se fez ou nao a tarefa proposta)
    bool click = false;
    bool release = false;
    bool collision1 = false;
    bool collision2 = false;
    bool collision3 = false;
    bool collision4 = false;
    bool collision5 = false;
    bool collision6 = false;
    bool Paused = false;

    int btnAction;
    
    // Declaraçoes para Inventario implementado em Lista LDE
    Color cor;
    bool menu = false;
    int seleciona = 0;
    Lista l;
    //------------------------------------------------------------------------

    const char msg1[50] = "Press ENTER or CLICK to Continue!";
    const char msg2[50] = "Are you sure?";
    const char msg3[256] = {"Gameplay and Art - Giulia \n Combat and Art - Mateus \n Main Menu and Battle Menu - Yuri \n Musica and Inventory - Octavio"};

    Vector2 mousePoint = {0.0f, 0.0f};
    Vector2 fontPos = {screenWidth / 2.0f - MeasureTextEx(fonte, msg1, 20, 2).x / 2, screenHeight / 1.5f + 100};
    Vector2 fontPos2 = {screenWidth / 2.0f - MeasureTextEx(fonte, msg2, 20, 2).x / 2, screenHeight / 2.0f - 100};
    Vector2 fontPos3 = {screenWidth / 2.0f - MeasureTextEx(fonte, msg3, 30, 2).x / 2, screenHeight / 2.0f - 100};

    // Inicia o mapa na posiçao 0.0 e define sua velocidade
    Vector2 mapPos = {0.0, 0.0};

    float speed = 5.0;

    // Vetor de posição da animação parada
    Vector2 position = {350.0f, 280.0f};
    // Retângulo que delimita o frame apresentado
    Rectangle frameRec = {0.0f, 0.0f, (float)zip.width / 6, (float)zip.height};
    // Inicia no frame 0
    int currentFrame = 0;

    // Contador e Velocidade de frame (por segundo)
    int framesCounter = 0;
    int framesSpeed = 8; // Number of spritesheet frames shown by second

    MenuScreen CurrentScreen = LOGO; //definição da tela de menu

    SetTargetFPS(60); //fps do jogo

    // cria lista inventario
    cria(&l);

    // insere itens no inventario
    insere(&l, 103, 3, "apenas um item", "item 1");
    insere(&l, 244, 8, "apenas um item", "item 2");
    insere(&l, 399, 5, "apenas um item", "item 3");
    insere(&l, 415, 7, "apenas um item", "item 4");
    //--------------------------------------------------------------------------------------
    PlayMusicStream(music); //Inicia a musica
    
    // enquanto a janela nao fechar
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music); //da Update na musica durante o jogo
        // check de colisoes
        mousePoint = GetMousePosition();
        collision1 = CheckCollisionPointRec(mousePoint, Button1);
        collision2 = CheckCollisionPointRec(mousePoint, Button2);
        collision3 = CheckCollisionPointRec(mousePoint, Button3);
        collision6 = CheckCollisionPointRec(mousePoint, Button4);
        collision4 = CheckCollisionPointRec(mousePoint, ButtonExitYes);
        collision5 = CheckCollisionPointRec(mousePoint, ButtonExitNo);
        click = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        release = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);

        // switch de áreas da tela
        switch (CurrentScreen)
        {
        case LOGO: //Logo inicial
        {
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER) || IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                CurrentScreen = MENU; //muda a tela
        }
        break;

        case MENU:
        {
            if (collision1)
            {
                if (click)
                {
                    btnAction = 1;
                }
                else if (release || IsKeyPressed(KEY_ENTER))
                {

                    // Define o Pause
                    Paused = false;

                    // Enquanto a janela de jogo não fechar, o código não é executado
                    while (!WindowShouldClose())
                    {
                       
                        //----------------------------------------------------------------------------------
                        //se apertar espaço o jogo pausa
                        if (IsKeyPressed(KEY_SPACE))
                            Paused = !Paused;

                        if (menu)
                        {
                            if (IsKeyPressed(KEY_Q))
                                menu = false;
                        }
                        else
                        {
                            if (IsKeyPressed(KEY_Q))
                                menu = true;
                        }

                        if (!Paused || !menu)
                        {

                            if (IsKeyPressed(KEY_N))
                            {
                                saveKeyPressed = true;
                            }

                            if (IsKeyPressed(KEY_M))
                            {
                                loadKeyPressed = true;
                            }

                            if (saveKeyPressed)
                            {
                                SaveGame(&gameData, saveFile);
                                saveKeyPressed = false;
                            }

                            if (loadKeyPressed)
                            {
                                gameData = LoadGame(saveFile);
                                loadKeyPressed = false;
                            }

                            framesCounter++;

                            if (framesCounter >= (60 / framesSpeed))
                            {
                                framesCounter = 0;
                                currentFrame++;

                                if (currentFrame > 5)
                                    currentFrame = 0;

                                frameRec.x = (float)currentFrame * (float)zip.width / 6;
                            }

                            //----------------------------------------------------------------------------------
                        }
                        // Draw
                        //----------------------------------------------------------------------------------
                        BeginDrawing();

                        // Desenha o mapa ==> imagem, posição na tela, rotação, tamanho, cor da imagem
                        ClearBackground(ZIPBLUE);
                        UpdateMusicStream(music);

                        // Desenha o mapa
                        DrawTextureEx(background, mapPos, 0.0, 4.0, WHITE);

                        Vector2 direction = {};
                        if (IsKeyDown(KEY_A)) //animação do personagem para esquerda e movimento
                        {
                            direction.x -= 1.0;

                            DrawTextureRec(left, frameRec, position, WHITE); 
                        }
                        if (IsKeyDown(KEY_D)) //animação do personagem para a direita e movimento
                        {
                            direction.x += 1.0;
                            DrawTextureRec(right, frameRec, position, WHITE); 
                        }
                        if (IsKeyDown(KEY_W)) //animação do personagem para cima e movimento
                        {
                            direction.y -= 1.0;
                            DrawTextureRec(up, frameRec, position, WHITE); 
                        }
                        if (IsKeyDown(KEY_S)) //animação do personagem para baixo e movimenoto
                        {
                            direction.y += 1.0;
                            DrawTextureRec(down, frameRec, position, WHITE); 
                        }
                        if (Vector2Length(direction) != 0.0)
                        {
                            // Vector 2 pega o valor de um vetor e normaliza para 1
                            // Impede que o gato ande mais rapido na diagonal
                            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
                        }
                        else
                        {
                            DrawTextureRec(zip, frameRec, position, WHITE); 
                        }

                        //Escreve na tela os atributos de level, vida e o Nome do personagem
                        DrawText(TextFormat("%s", gameData.name), 10, 10, 30, BLACK);
                        DrawText(TextFormat("HP: %d", gameData.Life), 100, 10, 20, BLACK);
                        DrawText(TextFormat("Level: %d", gameData.level), 200, 10, 20, BLACK);

                        if (Paused && !menu)
                        {
                            DrawText("Paused", 600, 380, 40, GREEN); //pause
                        }

                        if (menu)
                        {
                            janelaMenu(&seleciona, l);
                        }

                        EndDrawing();

                        //----------------------------------------------------------------------------------
                    }

                    // De-Initialization
                    //--------------------------------------------------------------------------------------
                    UnloadTexture(zip); // Texture unload

                    return 1;
                }
            }

            if (collision2) //Muda a tela no inicial
            {
                if (click)
                {
                    btnAction = 2;
                }
                else if (release)
                {
                    CurrentScreen = CREDITS;
                }
            }

            if (collision3) //Muda a tela para o exit game
            {
                if (click)
                {
                    btnAction = 3;
                }
                else if (release)
                {
                    CurrentScreen = EXIT;
                }
            }
        }
        break;

        case CREDITS:
        {
            if (collision6)
            {
                if (click)
                {
                    btnAction = 2;
                }
                else if (release)
                {
                    CurrentScreen = MENU;
                }
            }
        }
        break;

        case EXIT:
        {
            if (collision4)
            {
                if (click)
                {
                    btnAction = 1;
                }
                else if (release)
                {
                    //Unload de texturas ao sair
                    
                    UnloadTexture(buttonNew);
                    UnloadTexture(buttonCred);
                    UnloadTexture(buttonExit);
                    UnloadTexture(buttonYes);
                    UnloadTexture(buttonNo);
                    UnloadTexture(buttonBack);
                    CloseWindow();
                    return 0;
                }
            }

            if (collision5)
            {
                if (click)
                {
                    btnAction = 2;
                }
                else if (release)
                {
                    CurrentScreen = MENU;
                }
            }
        }
        break;
        }

        //  -----------------------------------------------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (CurrentScreen)
        {
        case LOGO:
        { //desenha a tela da logo
            DrawTexture(logo, 0, 0, WHITE);
            DrawTextEx(fonte, msg1, fontPos, 20, 2, GREEN);
        }
        break;

        case MENU: //desenha a tela do menu
        {
            DrawTexture(menu1, 5, 2.5, WHITE);
            drawMenu(Button1, Button2, Button3, buttonNew, buttonExit, buttonCred, collision1, collision2, collision3, btnAction, &cor);
        }
        break;

        case CREDITS: //desenha a tela de creditos
        {
            ClearBackground(RAYWHITE);
            DrawTextEx(fonte, msg3, fontPos3, 25, 2, VIOLET);
            drawCredits(buttonBack, collision6, &cor, btnAction, Button4);
        }
        break;

        case EXIT: //desenha a tela de exit game
        {
            DrawTextEx(fonte, msg2, fontPos2, 20, 2, VIOLET);
            drawExit(buttonYes, buttonNo, collision4, collision5, &cor, btnAction);
        }
        break;
        }

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(buttonNew);
    UnloadTexture(buttonCred);
    UnloadTexture(buttonExit);
    UnloadTexture(buttonYes);
    UnloadTexture(buttonNo);
    UnloadTexture(buttonBack);
    UnloadMusicStream(music);

    CloseWindow();
    CloseAudioDevice();
    //--------------------------------------------------------------------------------------

    return 0;
}