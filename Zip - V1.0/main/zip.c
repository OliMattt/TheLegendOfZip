/*******************************************************************************************
*
*   Trabalho de LAB AED-1
*
*   Nomes:  Giulia Ramos Bagodi
*           Mateus Pereira de Oliveira
*           Yuri Soinaktvitz Stockler
*

Criação de um jogo em C utilizando a biblioteca raylib.h
    
    Nosso projeto constitui de um jogo de RPG 2D,
    o qual você acompanha os primórdios do surgimento do Zip,
    um gatinho aprendiz de magia (e nosso herói) que mora em um mundo de computador
    onde feitiços são dados por códigos, bugs são uma ameaça perigosa
    que tomaram conta do reino e nosso gatinho aprendiz tem que salvar o mundo.

    Nosso código foi separado em dois, devido ao pouco tempo de produção
    Um exibe o mapa, as animações, a câmera e o movimento do Zip
    O segundo exibe nosso protótipo de batalha
    
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

float gatoX = 100;
float gatoY = 100;

float enemyX = 200;
float enemyY = 200;

typedef enum MenuScreen { LOGO, MENU, CREDITS, EXIT } MenuScreen;

int main(int)
{
    // tamanho da janela
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "The Legend of Zip");
    InitAudioDevice();
    
    //Declaração de sons
    Sound newgame = LoadSound("resources/newgame.wav");
    Sound creditos = LoadSound("resources/creditos.wav");
    Sound return1 = LoadSound("resources/return.wav");
    Sound exit = LoadSound("resources/exit.wav");
    Sound back = LoadSound("resources/back.wav");
    //-----------------------------------------------------------------
    
    //Declarações de textura
    Font fonte = LoadFont("resources/pixantiqua.png");
    Texture2D logo = LoadTexture("resources/Logo.png");
    Texture2D menu1 = LoadTexture("resources/zip.png");
    Texture2D buttonNew = LoadTexture("resources/ButtonNewGame.png");
    Texture2D buttonCred = LoadTexture("resources/ButtonCredits.png");
    Texture2D buttonExit = LoadTexture("resources/ButtonExit.png");
    Texture2D buttonYes = LoadTexture("resources/ButtonYes.png");
    Texture2D buttonNo = LoadTexture("resources/ButtonNo.png");
    Texture2D buttonBack = LoadTexture("resources/ButtonBack.png");
    //-----------------------------------------------------------------------
    
    //Declaração de retangulos dos botoes (colisao)
    Rectangle Button1 = {144, 100, 112, 25};
    Rectangle Button2 = {144, 150, 112, 25};
    Rectangle Button3 = {144, 200, 112, 25};
    Rectangle Button4 = {344, 350, 112, 25};    
    
    Rectangle ButtonExitYes = {244, 300, 122, 25};
    Rectangle ButtonExitNo = {456, 300, 112, 25};
    //----------------------------------------------------------------------
    
    //check (padrao falso para verificação se fez ou nao a tarefa proposta)
    bool click = false;
    bool release = false;
    bool collision1 = false;
    bool btnAction1 = false;
    bool collision2 = false;
    bool btnAction2 = false;
    bool collision3 = false;
    bool btnAction3 = false;
    bool collision4 = false;
    bool collision5 = false;
    bool collision6 = false;
    bool Paused = false;
    //------------------------------------------------------------------------
    
    // declaracoes de batalha
    // --------------------------------------------------------------------------
    
    
   /* Texture2D ButtonCombatOff = LoadTexture("resources/ButOff.png");
    Texture2D ButtonCombatSel = LoadTexture("resources/ButSel.png");
    Texture2D ButtonCombatOn = LoadTexture("resources/ButOn.png");
    Texture2D buttonYes = LoadTexture("resources/ButtonYes.png");
    Texture2D buttonNo = LoadTexture("resources/ButtonNo.png");
    Texture2D Enemy = LoadTexture("resources/bug1.png");
    Texture2D Hero = LoadTexture("resources/zip2.png");
    Texture2D background = LoadTexture("resources/poke.png");
    
    Rectangle BattleMenu = {100, 400, 600, 150};
    Rectangle BattleMagic1 = {200, 425, 112, 25};
    Rectangle BattleMagic2 = {200, 500, 112, 25};
    Rectangle BattleHeal = {500, 425, 112, 25};
    Rectangle BattleRun = {500, 500, 112, 25};
    Rectangle ButtonExitYes = {200, 475, 122, 25};
    Rectangle ButtonExitNo = {500, 475, 112, 25};
    
    bool click = false; //recebe o click do mouse
    bool release = false; //recebe o soltar do botão do mouse
    bool enter = false;
    bool collision12 = false; //recebe true quando há colisão entre o mouse e o retangulo do botão 1
    bool btnAction12 = false; //recebe true quando há click do mouse com colisão 1 true, utilizado para atualizar textura do botão normal para botão pressionado
    bool collision13 = false;
    bool btnAction13 = false;
    bool collision14 = false;
    bool btnAction14 = false;
    bool collision15 = false;
    bool btnAction15 = false;
    bool collision16 = false;
    bool collision17 = false;

    
    //int battleRound = 1;
    int enemyLife = 100;
    int heroLife = 100;
    //int n;
   */
    
    // ----------------------------------------------------------------------------
    const char msg1[50] = "Press ENTER or CLICK to Continue!";
    const char msg2[50] = "Are you sure?";
    const char msg3[256] = { "Gameplay and Art - Giulia \n Combat and Art - Mateus \n Main Menu and Battle Menu - Yuri"};
    
    Vector2 mousePoint = { 0.0f, 0.0f };
    Vector2 fontPos = {screenWidth/2.0f - MeasureTextEx(fonte, msg1, 20, 2).x/2, screenHeight/1.5f + 100};
    Vector2 fontPos2 = {screenWidth/2.0f - MeasureTextEx(fonte, msg2, 20, 2).x/2, screenHeight/2.0f - 100};
    Vector2 fontPos3 = {screenWidth/2.0f - MeasureTextEx(fonte, msg3, 30, 2).x/2, screenHeight/2.0f - 100};
    
    MenuScreen CurrentScreen = LOGO;
    

    SetTargetFPS(60);               
    //--------------------------------------------------------------------------------------

    //enquanto a janela nao fechar
    while (!WindowShouldClose())    
    {
        //check de colisoes
        mousePoint = GetMousePosition();
        collision1 = CheckCollisionPointRec(mousePoint, Button1);
        collision2 = CheckCollisionPointRec(mousePoint, Button2);
        collision3 = CheckCollisionPointRec(mousePoint, Button3);
        collision6 = CheckCollisionPointRec(mousePoint, Button4);
        collision4 = CheckCollisionPointRec(mousePoint, ButtonExitYes);   
        collision5 = CheckCollisionPointRec(mousePoint, ButtonExitNo);   
        click = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        release = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        
        //switch de áreas da tela
    switch(CurrentScreen)
    {
        case LOGO:
        {
            if (IsKeyPressed(KEY_ENTER)||IsKeyPressed(KEY_KP_ENTER)||IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) CurrentScreen = MENU;
        } break;
        
        case MENU:
        {
            if (collision1)
            {   
                if(click){
                    btnAction1 = true;
                    PlaySoundMulti(newgame);
                }
                else if (release || IsKeyPressed(KEY_ENTER)){
                        
// Define o Pause
    bool Paused = false;

    Texture2D background = LoadTexture("resources/mapa1.png");
    Texture2D zip = LoadTexture("resources/personagens/zip.png");        // Texture loading
    
//Inicia o mapa na posiçao 0.0 e define sua velocidade
    Vector2 mapPos={0.0, 0.0};
    float speed = 5.0;
    
// Vetor de posição do gato
    Vector2 zipPos = {
        (float)screenWidth/2.0f - 4.0f * (0.5f * (float)zip.width/7.0f),
        (float)screenHeight/2.0f - 4.0f * (0.5f * (float)zip.height)
    };

// Vetor de posição da animação parada
// Retângulo que delimita o frame apresentado
// Inicia no frame 0
    Vector2 position = { 350.0f, 280.0f };
    Rectangle frameRec = { 0.0f, 0.0f, (float)zip.width/6, (float)zip.height };
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

            frameRec.x = (float)currentFrame*(float)zip.width/6;
        }

        
        //----------------------------------------------------------------------------------
    }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // Desenha o mapa ==> imagem, posição na tela, rotação, tamanho, cor da imagem
            ClearBackground(RAYWHITE);
            
        Vector2 direction = {};
            if (IsKeyDown(KEY_A))   direction.x -= 1.0;
            if (IsKeyDown(KEY_D))   direction.x += 1.0;
            if (IsKeyDown(KEY_W))   direction.y -= 1.0;
            if (IsKeyDown(KEY_S))   direction.y += 1.0;
            if (Vector2Length(direction) != 0.0)
        {
            // set mapPod = mapPos - direction
            
            //Vector 2 pega o valor de um vetor e normaliza para 1
            //Impede que o gato ande mais rapido na diagonal
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction),speed));
        }
            // Desenha o mapa
            DrawTextureEx(background, mapPos, 0.0, 4.0, WHITE);
            
            // Desenha parte das texturas do gato e o centraliza na tela
            
            Rectangle source = {0.f, 0.f, (float)zip.width/6.f, (float)zip.height};
            Rectangle dest = {zipPos.x, zipPos.y, 4.0f * (float)zip.width/6.0f, 4.0f * (float)zip.height};
            Vector2 origin = {};
            DrawTextureRec(zip, frameRec, position, WHITE);  // Draw part of the texture

            if (Paused)
                DrawText("Paused", 600, 380, 40, GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

/*
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        mousePoint = GetMousePosition();
        click = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        release = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        enter = IsKeyPressed(KEY_SPACE);
        collision12 = CheckCollisionPointRec(mousePoint, BattleMagic1);
        collision13 = CheckCollisionPointRec(mousePoint, BattleMagic2);
        collision14 = CheckCollisionPointRec(mousePoint, BattleHeal);
        collision15 = CheckCollisionPointRec(mousePoint, BattleRun);
        collision16 = CheckCollisionPointRec(mousePoint, ButtonExitYes);   
        collision17 = CheckCollisionPointRec(mousePoint, ButtonExitNo); 
        
        
        
    //while(battleRound == 1) // While crasha o programa
    
    switch(CurrentBattleScreen) 
    {
        case MENU:
        {
            if (collision12)
            {
                if(click){
                    btnAction12 = true;
                }
                else if (release){
                    CurrentBattleScreen = MAGIC1;
                }
                else{
                    btnAction12 = false;
                }
            }
            if (collision13)
            {
                if(click){
                    btnAction13 = true;
                }
                else if (release){
                    CurrentBattleScreen = MAGIC2;
                }
                else{
                    btnAction13 = false;
                }
            }
            
            if (collision14)
            {
                if(click){
                    btnAction14 = true;
                }
                else if (release){
                    CurrentBattleScreen = HEAL;
                }
                else{
                    btnAction14 = false;
                }
            }

            if (collision15)
            {
                if(click){
                    btnAction15 = true;
                }
                else if (release){
                    CurrentBattleScreen = RUN;
                }
                else{
                    btnAction15 = false;
                }
            }
            
            if(heroLife <= 0)
            {
                if(click)
                {
                    CurrentBattleScreen = DEFEAT;
                }
            }
            if(enemyLife <= 0)
            {
                if(click)
                {
                    CurrentBattleScreen = WIN;
                }
            }
        }break;
        
        case MAGIC1:
        {
           if(click){
               enemyLife = enemyLife - 10;
               CurrentBattleScreen = ENEMYATACK; 
           }
        }break;
        
        case MAGIC2:
        {
           if(click){
               enemyLife = enemyLife - 15;
               CurrentBattleScreen = ENEMYATACK;
           }
        }break;
        
        case HEAL:
        {
           if(click){
               heroLife = heroLife + 14;
               CurrentBattleScreen = ENEMYATACK;
           }
        }break;
        
        case RUN: 
        {   
            if (collision16)
            {
                if(click){
                    btnAction12 = true; 
                }
                else if (release){
                    CloseWindow();
                    return 0;
                }            
                else{
                    btnAction12 = false;
                }
            }
            if (collision17)
            {
                if(click){
                    btnAction13 = true; //se ocorrer colisão com o retangulo 2, detecta click do mouse e muda btnAction2 para true, para atualizar a textura do botão
                }
                else if (release){
                    CurrentBattleScreen = MENU; //se o botão for solto em cima do retangulo 2, volta para o menu
                }
                else{
                    btnAction13 = false;
                }
            }  
        }break;
        case ENEMYATACK:
        {  
            if (enter)
            {
                heroLife = heroLife - 12;
                CurrentBattleScreen = MENU;
            }  
        }break;
        
        case DEFEAT:
        {
            if (enter)
            {
                return 1;
            } 
        }break;
        
        case WIN:
        {
            if (enter)
            {
                return 0;
            } 
        }break;
    }
    

    // if(battleRound = 2)
    // {
    // switch(EnemyBattleScreen) 
        // {
            // case ENEMYOPENING:
            // {
                // if (click)
                // {   
                    // switch(RoundRandomSelect)
                    // {
                    // case RANDOMOPENING:
                    // {
                        // n = GetRandomValue(0, 2);
                        // if(n = 0) RoundRandomSelect = RANDOM1;
                        // else if(n = 1) RoundRandomSelect = RANDOM2;
                        // else if(n = 2) RoundRandomSelect = RANDOM3;
                        // else RoundRandomSelect = RANDOMHEAL;
                    // }break;
                    // case RANDOM1: {EnemyBattleScreen = ENEMYMAGIC1;} break;
                    // case RANDOM2: {EnemyBattleScreen = ENEMYMAGIC2;} break;
                    // case RANDOM3: {EnemyBattleScreen = ENEMYMAGIC3;} break;
                    // case RANDOMHEAL: {EnemyBattleScreen = ENEMYHEAL;} break;
                    // }
                // }

            // }break;
            
            // case ENEMYMAGIC1:
            // {
                // heroLife =- 10;
                // if (click)battleRound = 1;
            // }break;
            
            // case ENEMYMAGIC2:
            // {
                // heroLife =- 15;
                // if (click)battleRound = 1;
            // }break;
            
            // case ENEMYMAGIC3:
            // {
                // heroLife =- 20;
                // if (click)battleRound = 1;
            // }break;
            
            
            // case ENEMYHEAL:
            // {
                // enemyLife =+ 10;
                // if (click)battleRound = 1;
            // }break;
        // }
    // }
   
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);
    
    switch(CurrentBattleScreen) 
    {
        case MENU:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
            DrawRectangleRec(BattleMagic1, WHITE);
            DrawRectangleRec(BattleMagic2, WHITE);
            DrawRectangleRec(BattleHeal, WHITE);
            DrawRectangleRec(BattleRun, WHITE);
            DrawTexture(Enemy, 460, 50, WHITE);
            DrawTexture(Hero, 95, 144, WHITE);
            DrawText(TextFormat("%i", heroLife), 10, 180, 60, GREEN);
            DrawText(TextFormat("%i", enemyLife), 360, 180, 60, RED);
          
            
            if (collision1){
                    DrawTexture(ButtonCombatSel, 200, 425, WHITE);

                    if(btnAction1){
                        DrawTexture(ButtonCombatOn, 200, 425, WHITE);
                    }
                }
            else{
                    DrawTexture(ButtonCombatOff, 200, 425, WHITE);
                }
                
            if (collision2){
                    DrawTexture(ButtonCombatSel, 200, 500, WHITE);

                    if(btnAction2){
                        DrawTexture(ButtonCombatOn, 200, 500, WHITE);
                    }
                }
            else{
                    DrawTexture(ButtonCombatOff, 200, 500, WHITE);
                }
                
            if (collision3){
                    DrawTexture(ButtonCombatSel, 500, 425, WHITE);

                    if(btnAction3){
                        DrawTexture(ButtonCombatOn, 500, 425, WHITE);
                    }
                }
            else{
                    DrawTexture(ButtonCombatOff, 500, 425, WHITE);
                }
                
            if (collision4){
                    DrawTexture(ButtonCombatSel, 500, 500, WHITE);

                    if(btnAction4){
                        DrawTexture(ButtonCombatOn, 500, 500, WHITE);
                    }
                }
            else{
                    DrawTexture(ButtonCombatOff, 500, 500, WHITE);
                }
                
        }break;
        case MAGIC1:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
            DrawText("Magia 1 utilizada", 110, 420, 20, WHITE);
            DrawText("10 de dano", 110, 450, 20, WHITE);
            DrawTexture(Enemy, 460, 50, YELLOW);
            DrawTexture(Hero, 95, 144, WHITE);
        }break;
        case MAGIC2:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
            DrawText("Magia 2 utilizada", 110, 420, 20, WHITE);
            DrawText("15 de dano", 110, 450, 20, WHITE);
            DrawTexture(Enemy, 460, 50, RED);
            DrawTexture(Hero, 95, 144, WHITE);
        }break;
        
        case HEAL:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
            DrawText("Cura utilizada", 110, 420, 20, WHITE);
            DrawText("+12 de vida", 110, 450, 20, GREEN);
            DrawTexture(Enemy, 460, 50, WHITE);
            DrawTexture(Hero, 95, 144, GREEN);
        }break;
        
        case RUN:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
            DrawRectangleRec(ButtonExitYes, WHITE);
            DrawRectangleRec(ButtonExitNo, WHITE);
            DrawText("Vai correr?", 110, 410, 20, WHITE);
            DrawTexture(Enemy, 460, 50, WHITE);
            DrawTexture(Hero, 95, 144, WHITE);

            if (collision5){
                    DrawTexture(buttonYes, 220, 475, YELLOW);
            
                
                    if(btnAction1){
                        DrawTexture(buttonYes, 220, 475, RED);
                    }
                }
                else{
                    DrawTexture(buttonYes, 220, 475, WHITE);
                }
                DrawRectangleRec(ButtonExitYes, BLANK);
            
            
                if (collision6){
                    DrawTexture(buttonNo, 520, 475, YELLOW);;
            
                
                    if(btnAction2){
                        DrawTexture(buttonNo, 520, 475, RED);
                    }
                }
                else{
                    DrawTexture(buttonNo, 520, 475, WHITE);
                }
                DrawRectangleRec(ButtonExitNo, BLANK);
        }break;
        
        case ENEMYATACK:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
            DrawText("Bug used System(pause)", 110, 420, 20, WHITE);
            DrawText("-12 de vida", 110, 450, 20, RED);
            DrawTexture(Hero, 95, 144, RED);
            DrawTexture(Enemy, 46, 144, WHITE);
            
            
        }break;

        case DEFEAT:
        {
            UnloadTexture(ButtonCombatOff);
            UnloadTexture(ButtonCombatSel);
            UnloadTexture(ButtonCombatOn);
            UnloadTexture(buttonYes);
            UnloadTexture(buttonNo);
            UnloadTexture(Enemy);
            UnloadTexture(Hero);
            ClearBackground(BLACK);
            DrawText(TextFormat("Voce morreu"), 200, 180, 80, RED);
        }break;
        
        case WIN:
        {
            UnloadTexture(ButtonCombatOff);
            UnloadTexture(ButtonCombatSel);
            UnloadTexture(ButtonCombatOn);
            UnloadTexture(buttonYes);
            UnloadTexture(buttonNo);
            UnloadTexture(Enemy);
            UnloadTexture(Hero);
            ClearBackground(RAYWHITE);
            DrawText(TextFormat("Voce venceu"), 200, 180, 80, VIOLET);
        }break;
        
    }
    // if(battleRound = 2)
    // {
        // switch(EnemyBattleScreen) 
        // {
            // case ENEMYOPENING:
            // {
            // DrawRectangleRec(BattleMenu, BLACK);
            // DrawText("Enemy is attacking!", 110, 410, 20, WHITE);
            // DrawTexture(Enemy, 500, 5, WHITE);
            // DrawTexture(Hero, 100, 75, WHITE);
            // }break;
            
            // case ENEMYMAGIC1:
            // {
            // DrawRectangleRec(BattleMenu, BLACK);
            // DrawText("Inimigo: Magia 1 utilizada", 110, 420, 20, WHITE);
            // DrawTexture(Enemy, 500, 5, WHITE);
            // DrawTexture(Hero, 100, 75, YELLOW);
            // }break;
            
            // case ENEMYMAGIC2:
            // {
            // DrawRectangleRec(BattleMenu, BLACK);
            // DrawText("Inimigo: Magia 2 utilizada", 110, 420, 20, WHITE);
            // DrawTexture(Enemy, 500, 5, WHITE);
            // DrawTexture(Hero, 100, 75, YELLOW);
            // }break;
            
            // case ENEMYMAGIC3:
            // {
            // DrawRectangleRec(BattleMenu, BLACK);
            // DrawText("Inimigo: Magia 3 utilizada", 110, 420, 20, WHITE);
            // DrawTexture(Enemy, 500, 5, WHITE);
            // DrawTexture(Hero, 100, 75, YELLOW);
            // }break;
            
            // case ENEMYHEAL:
            // {
            // DrawRectangleRec(BattleMenu, BLACK);
            // DrawText("Cura utilizada", 110, 420, 20, WHITE);
            // DrawTexture(Enemy, 500, 5, GREEN);
            // DrawTexture(Hero, 100, 75, WHITE);
            // }break;
        // }
    // }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
*/
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(zip);       // Texture unloading
                       
                        
                    return 1;
                }            
                else{
                    btnAction1 = false;
                }
            }
        
            if (collision2)
            {
                if(click){
                    btnAction2 = true;
                    PlaySoundMulti(creditos);
                }
                else if (release){
                    CurrentScreen = CREDITS;
                }
                else{
                    btnAction2 = false;
                }
            }
        
            if (collision3)
            {
                if(click){
                    btnAction3 = true;
                    PlaySoundMulti(exit);
                    }
                else if (release){
                    CurrentScreen = EXIT;
                }
            }
                else{
                    btnAction3 = false;
                }
            } break;
        
        case CREDITS:
        {
            if (collision6)
            {
                if(click){
                    btnAction2 = true;
                    PlaySoundMulti(return1);
                }
                else if (release){
                    CurrentScreen = MENU;
                }
                else{
                    btnAction2 = false;
                    
                }
            }
        } break;
        
        case EXIT:
        {   
            if (collision4)
            {
                if(click){
                    btnAction1 = true;
                }
                else if (release){
                    
                        UnloadTexture(buttonNew);
                        UnloadTexture(buttonCred);
                        UnloadTexture(buttonExit);
                        UnloadTexture(buttonYes);
                        UnloadTexture(buttonNo);
                        UnloadTexture(buttonBack);
                        CloseWindow();
                    return 0;
                }            
                else{
                    btnAction1 = false;
                }
            }
        
            if (collision5)
            {
                if(click){
                    btnAction2 = true;
                    PlaySoundMulti(back);
                }
                else if (release){
                    CurrentScreen = MENU;
                    
                }
                else{
                    btnAction2 = false;
                }
            }
        } break; 
    }


//  -----------------------------------------------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        
            
        switch(CurrentScreen)
        {
            case LOGO:
            {
                DrawTexture(logo, 0, 0, WHITE);
                DrawTextEx(fonte, msg1, fontPos, 20, 2, GREEN);
            } break;
        
            case MENU:
            {
                DrawTexture(menu1, 5, 2.5, WHITE);
            
                if (collision1){
                    DrawTexture(buttonNew, 144, 100, YELLOW);
                
                    if(btnAction1){
                        DrawTexture(buttonNew, 144, 100, RED);
                    }
                }
                else{
                    DrawTexture(buttonNew, 144, 100, WHITE);
                }
                DrawRectangleRec(Button1, BLANK);
                 
                if (collision2){
                    DrawTexture(buttonCred, 144, 150, YELLOW);

                    if(btnAction2){
                        DrawTexture(buttonCred, 144, 150, RED);
                    }
                }
                else{
                    DrawTexture(buttonCred, 144, 150, WHITE);
                }
                DrawRectangleRec(Button2, BLANK);
            
                if (collision3){
                    DrawTexture(buttonExit, 144, 200, YELLOW);;

                    if(btnAction3){
                        DrawTexture(buttonExit, 144, 200, RED);
                    }
                }
                else{
                    DrawTexture(buttonExit, 144, 200, WHITE);
                }
                DrawRectangleRec(Button3, BLANK);  
            }
            break;
        
            case CREDITS:
            {   
                ClearBackground(RAYWHITE);
                DrawTextEx(fonte, msg3, fontPos3, 25, 2, VIOLET);
            
                if (collision6){
                    DrawTexture(buttonBack, 344, 350, YELLOW);;
            
                    if(btnAction2){
                        DrawTexture(buttonBack, 344, 350, RED);
                    }
                }
                else{
                    DrawTexture(buttonBack, 344, 350, WHITE);
                }
                DrawRectangleRec(Button4, BLANK);
            } break;
        
            case EXIT:
            {
                DrawTextEx(fonte, msg2, fontPos2, 20, 2, VIOLET);
            
                if (collision4){
                    DrawTexture(buttonYes, 244, 300, YELLOW);
            
                
                    if(btnAction1){
                        DrawTexture(buttonYes, 244, 300, RED);
                    }
                }
                else{
                    DrawTexture(buttonYes, 244, 300, WHITE);
                }
                DrawRectangleRec(ButtonExitYes, BLANK);
            
            
                if (collision5){
                    DrawTexture(buttonNo, 456, 300, YELLOW);;
            
                
                    if(btnAction2){
                        DrawTexture(buttonNo, 456, 300, RED);
                    }
                }
                else{
                    DrawTexture(buttonNo, 456, 300, WHITE);
                }
                DrawRectangleRec(ButtonExitNo, BLANK);
            } break;
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
    
    CloseWindow();
    CloseAudioDevice();
    //--------------------------------------------------------------------------------------

    return 0;
}
void movInim(void){
    if (IsKeyDown(KEY_D)) enemyX += 5;
    if (IsKeyDown(KEY_A)) enemyX -= 5;
    if (IsKeyDown(KEY_S)) enemyY += 5;
    if (IsKeyDown(KEY_W)) enemyY -= 5;
return;
}
