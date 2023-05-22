

#include "raylib.h"


typedef enum BattleScreen { MENU, MAGIC1, MAGIC2, HEAL, RUN, WIN, DEFEAT, ENEMYATACK } BattleScreen;
// typedef enum EnemyRound { ENEMYOPENING, ENEMYMAGIC1, ENEMYMAGIC2, ENEMYMAGIC3, ENEMYHEAL } EnemyRound;
// typedef enum RoundSelect { RANDOMOPENING, RANDOM1, RANDOM2, RANDOM3, RANDOMHEAL } RoundSelect;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    Texture2D ButtonCombatOff = LoadTexture("resources/ButOff.png");
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
    bool collision1 = false; //recebe true quando há colisão entre o mouse e o retangulo do botão 1
    bool btnAction1 = false; //recebe true quando há click do mouse com colisão 1 true, utilizado para atualizar textura do botão normal para botão pressionado
    bool collision2 = false;
    bool btnAction2 = false;
    bool collision3 = false;
    bool btnAction3 = false;
    bool collision4 = false;
    bool btnAction4 = false;
    bool collision5 = false;
    bool collision6 = false;

    
    //int battleRound = 1;
    int enemyLife = 100;
    int heroLife = 100;
    //int n;
    
    Vector2 mousePoint = { 0.0f, 0.0f };
    Vector2 mapPos={0.0, 0.0};

    BattleScreen CurrentBattleScreen = MENU;
    // EnemyRound EnemyBattleScreen = ENEMYOPENING;
    // RoundSelect RoundRandomSelect = RANDOMOPENING;
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        mousePoint = GetMousePosition();
        click = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        release = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
        enter = IsKeyPressed(KEY_SPACE);
        collision1 = CheckCollisionPointRec(mousePoint, BattleMagic1);
        collision2 = CheckCollisionPointRec(mousePoint, BattleMagic2);
        collision3 = CheckCollisionPointRec(mousePoint, BattleHeal);
        collision4 = CheckCollisionPointRec(mousePoint, BattleRun);
        collision5 = CheckCollisionPointRec(mousePoint, ButtonExitYes);   
        collision6 = CheckCollisionPointRec(mousePoint, ButtonExitNo); 
        
        
        
    //while(battleRound == 1) // While crasha o programa
    
    switch(CurrentBattleScreen) 
    {
        case MENU:
        {
            if (collision1)
            {
                if(click){
                    btnAction1 = true;
                }
                else if (release){
                    CurrentBattleScreen = MAGIC1;
                }
                else{
                    btnAction1 = false;
                }
            }
            if (collision2)
            {
                if(click){
                    btnAction2 = true;
                }
                else if (release){
                    CurrentBattleScreen = MAGIC2;
                }
                else{
                    btnAction2 = false;
                }
            }
            
            if (collision3)
            {
                if(click){
                    btnAction3 = true;
                }
                else if (release){
                    CurrentBattleScreen = HEAL;
                }
                else{
                    btnAction3 = false;
                }
            }

            if (collision4)
            {
                if(click){
                    btnAction4 = true;
                }
                else if (release){
                    CurrentBattleScreen = RUN;
                }
                else{
                    btnAction4 = false;
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
            if (collision5)
            {
                if(click){
                    btnAction1 = true; 
                }
                else if (release){
                    CloseWindow();
                    return 0;
                }            
                else{
                    btnAction1 = false;
                }
            }
            if (collision6)
            {
                if(click){
                    btnAction2 = true; //se ocorrer colisão com o retangulo 2, detecta click do mouse e muda btnAction2 para true, para atualizar a textura do botão
                }
                else if (release){
                    CurrentBattleScreen = MENU; //se o botão for solto em cima do retangulo 2, volta para o menu
                }
                else{
                    btnAction2 = false;
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
            DrawText("Bug used 'System("pause");'", 110, 420, 20, WHITE);
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

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}