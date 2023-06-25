
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "raylib.h"

typedef enum BattleScreen { MENU, MAGIC1, MAGIC2, HEAL, RUN, WIN, DEFEAT, ENEMYATACK } BattleScreen;

struct Enemy_Status {

    int vida;
    int dano_base;

};

struct Zip_Status {

    int vidaZip;
    int DMG_Base;
};

struct Modificadores {

    int modificadorDMG, modificadorVida;

};
typedef struct no {
    int dado;
    struct no *prox; 
} No;

typedef struct {
    No *topo;
    int tamPilha;
} Pilha;


void cria(Pilha *s);
int empilha(Pilha *s, int dado);
int desempilha(Pilha *s, int *dado);
//void mostra(Pilha s);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    struct Enemy_Status EnemyTutorial = {25, 3};
    struct Enemy_Status EnemyLow = {35, 5};
    struct Enemy_Status EnemyMid = {50, 7};
    struct Enemy_Status EnemyBOSS = {200, 15};
    struct Zip_Status Zip = {200, 10};
    struct Modificadores ModTutorial = {0, -3};
    struct Modificadores ModLow = {1, 2};
    struct Modificadores ModMid = {2, 4};
    struct Modificadores ModHigh = {4, 6};
    struct Modificadores ModBOSS = {8, 15};

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    //Funcoes de pilha----------------------
    
    Pilha s;
    int dado;
    srand(time(NULL));

    cria(&s);
    
    for(int i=0; i < 1000; i++){
        dado = rand() % 5;
        empilha(&s, dado);
        }
    
    //mostra(s);
    
    //-------------------------------------

    InitWindow(screenWidth, screenHeight, "Battle Menu");
    
    Texture2D Enemy = LoadTexture("resources/bug1.png");
    Texture2D background = LoadTexture("resources/poke2.png");
    Texture2D zip = LoadTexture("resources/zip.png");
    
    Font fonte = LoadFontEx("resources/pixantiqua.ttf", 32, 0, 250);
    
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
    int enemyLife = EnemyBOSS.vida;
    int heroLife = Zip.vidaZip;
    //int n;
    
    Vector2 mousePoint = { 0.0f, 0.0f };
    Vector2 mapPos={0.0, 0.0};
    
    Vector2 zipPos = { 175.0f, 280.0f };
    Vector2 enemyPos = { 450.0f, 155.0f };
    Vector2 enemyAttackPos = { 175.0f, 155.0f };

    Rectangle frameRec = { 0.0f, 0.0f, (float)zip.width/6, (float)zip.height };
    Rectangle attack1 = { 0.0f, 0.0f, (float)zip.width, (float)zip.height };
    Rectangle frameRecEnemy = { 0.0f, 0.0f, (float)Enemy.width, (float)Enemy.height };
    

    BattleScreen CurrentBattleScreen = MENU;
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        mousePoint = GetMousePosition();
        click = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        release = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
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
               enemyLife = enemyLife - Zip.DMG_Base;
               CurrentBattleScreen = ENEMYATACK; 
           }
        }break;
        
        case MAGIC2:
        {
           if(click){
               enemyLife = enemyLife - (Zip.DMG_Base + 6);
               CurrentBattleScreen = ENEMYATACK;
           }
        }break;
        
        case HEAL:
        {
           if(click){
               heroLife = heroLife + 20;
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
            if (release)
            {
                desempilha(&s, &dado);
                    
                    if(dado == 0){
                        heroLife = heroLife - 10;
                        CurrentBattleScreen = MENU;
                    }
                    if(dado == 1){
                        heroLife = heroLife - 12;
                        CurrentBattleScreen = MENU;
                    }
                    if(dado == 2){
                        heroLife = heroLife - 16;
                        CurrentBattleScreen = MENU;
                    }
                    if(dado == 3){
                        enemyLife = enemyLife - 10;
                        CurrentBattleScreen = MENU;
                    }
                     if(dado == 4){
                        heroLife = heroLife - 30;
                        CurrentBattleScreen = MENU;
                        enemyLife = enemyLife + 5;
                    }

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
            DrawRectangleRec(BattleMagic1, BLANK);
            DrawRectangleRec(BattleMagic2, BLANK);
            DrawRectangleRec(BattleHeal, BLANK);
            DrawRectangleRec(BattleRun, BLANK);
            DrawTextureRec(Enemy, frameRecEnemy, enemyPos, WHITE);
            DrawTextureRec(zip, frameRec, zipPos, WHITE); 
            DrawTextEx(fonte, TextFormat("%i", heroLife), (Vector2){ 10, 180}, 60, 2, DARKPURPLE);
            DrawTextEx(fonte, TextFormat("%i", enemyLife), (Vector2){ 680, 180}, 60, 2, RED);
          
            
            if (collision1){
                    DrawTextEx(fonte, "Magia 1", (Vector2){ 200, 425}, (float)fonte.baseSize, 2, YELLOW);

                    if(btnAction1){
                        DrawTextEx(fonte, "Magia 1", (Vector2){ 200, 425}, (float)fonte.baseSize, 2, GREEN);
                    }
                }
            else{
                    DrawTextEx(fonte, "Magia 1", (Vector2){ 200, 425}, (float)fonte.baseSize, 2, DARKPURPLE);
                }
                
            if (collision2){
                    DrawTextEx(fonte, "Magia 2", (Vector2){ 200, 500}, (float)fonte.baseSize, 2, YELLOW);

                    if(btnAction2){
                        DrawTextEx(fonte, "Magia 2", (Vector2){ 200, 500}, (float)fonte.baseSize, 2, GREEN);
                    }
                }
            else{
                    DrawTextEx(fonte, "Magia 2", (Vector2){ 200, 500}, (float)fonte.baseSize, 2, DARKPURPLE);
                }
                
            if (collision3){
                    DrawTextEx(fonte, "Cura", (Vector2){ 500, 425}, (float)fonte.baseSize, 2, YELLOW);

                    if(btnAction3){
                        DrawTextEx(fonte, "Cura", (Vector2){ 500, 425}, (float)fonte.baseSize, 2, GREEN);
                    }
                }
            else{
                    DrawTextEx(fonte, "Cura", (Vector2){ 500, 425}, (float)fonte.baseSize, 2, DARKPURPLE);
                }
                
            if (collision4){
                    DrawTextEx(fonte, "Correr", (Vector2){ 500, 500}, (float)fonte.baseSize, 2, YELLOW);

                    if(btnAction4){
                        DrawTextEx(fonte, "Correr", (Vector2){ 500, 500}, (float)fonte.baseSize, 2, GREEN);
                    }
                }
            else{
                    DrawTextEx(fonte, "Correr", (Vector2){ 500, 500}, (float)fonte.baseSize, 2, DARKPURPLE);
                }
                
        }break;
        case MAGIC1:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
            DrawTextEx(fonte, "Magia 1 utilizada!", (Vector2){ 110.0f, 420.0f}, (float)fonte.baseSize, 2, DARKPURPLE);
            DrawTextEx(fonte, "10 de dano!", (Vector2){ 110, 460}, (float)fonte.baseSize, 2, RED);
            DrawTextureRec(Enemy, frameRecEnemy, enemyPos, YELLOW);
            DrawTextureRec(zip, frameRec, zipPos, WHITE);
        }break;
        case MAGIC2:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
            DrawTextEx(fonte, "Magia 2 utilizada!", (Vector2){ 110.0f, 420.0f}, (float)fonte.baseSize, 2, DARKPURPLE);
            DrawTextEx(fonte, "15 de dano!", (Vector2){ 110, 460}, (float)fonte.baseSize, 2, RED);
            DrawTextureRec(Enemy, frameRecEnemy, enemyPos, RED);
            DrawTextureRec(zip, attack1, zipPos, WHITE);
        }break;
        
        case HEAL:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
            DrawTextEx(fonte, "Cura utilizada", (Vector2){ 110.0f, 420.0f}, (float)fonte.baseSize, 2, DARKPURPLE);
            DrawTextEx(fonte, "+20 de vida", (Vector2){ 110, 460}, (float)fonte.baseSize, 2, GREEN);
            DrawTextureRec(Enemy, frameRecEnemy, enemyPos, WHITE);
            DrawTextureRec(zip, frameRec, zipPos, GREEN);
        }break;
        
        case RUN:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
            DrawRectangleRec(ButtonExitYes, BLANK);
            DrawRectangleRec(ButtonExitNo, BLANK);
            DrawTextEx(fonte, "Vai correr?", (Vector2){ 110.0f, 420.0f}, (float)fonte.baseSize, 2, DARKPURPLE);
            DrawTextureRec(Enemy, frameRecEnemy, enemyPos, WHITE);
            DrawTextureRec(zip, frameRec, zipPos, WHITE);

            if (collision5){
                    //DrawTexture(buttonYes, 220, 475, YELLOW);
                    DrawTextEx(fonte, "Sim", (Vector2){ 220, 475}, (float)fonte.baseSize, 2, YELLOW);
            
                
                if(btnAction1){
                        //DrawTexture(buttonYes, 220, 475, RED);
                        DrawTextEx(fonte, "Sim", (Vector2){ 220, 475}, (float)fonte.baseSize, 2, RED);
                    }
                }
                else{
                    DrawTextEx(fonte, "Sim", (Vector2){ 220, 475}, (float)fonte.baseSize, 2, DARKPURPLE);
                }
                DrawRectangleRec(ButtonExitYes, BLANK);
            
            
                if (collision6){
                    DrawTextEx(fonte, "Não!", (Vector2){ 520, 475}, (float)fonte.baseSize, 2, YELLOW);
            
                
                    if(btnAction2){
                        DrawTextEx(fonte, "Não!", (Vector2){ 520, 475}, (float)fonte.baseSize, 2, RED);
                    }
                }
                else{
                    DrawTextEx(fonte, "Não!", (Vector2){ 520, 475}, (float)fonte.baseSize, 2, DARKPURPLE);
                }
                DrawRectangleRec(ButtonExitNo, BLANK);
        }break;
        
        case ENEMYATACK:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
                if(dado == 0){
                        DrawTextEx(fonte, "Zip -10 de vida", (Vector2){ 110, 450}, (float)fonte.baseSize, 2, RED);
                        DrawTextureRec(zip, frameRec, zipPos, RED);
                        DrawTextureRec(Enemy, frameRecEnemy, enemyAttackPos, WHITE);
                    }
                if(dado == 1){
                        DrawTextEx(fonte, "Zip -15 de vida", (Vector2){ 110, 450}, (float)fonte.baseSize, 2, RED);
                        DrawTextureRec(zip, frameRec, zipPos, RED);
                        DrawTextureRec(Enemy, frameRecEnemy, enemyAttackPos, WHITE);
                    }
                if(dado == 2){
                        DrawTextEx(fonte, "Zip -20 de vida", (Vector2){ 110, 450}, (float)fonte.baseSize, 2, RED);
                        DrawTextureRec(zip, frameRec, zipPos, RED);
                        DrawTextureRec(Enemy, frameRecEnemy, enemyAttackPos, WHITE);
                    }
                if(dado == 3){
                        DrawTextEx(fonte, "Bug +10 de vida", (Vector2){ 110, 450}, (float)fonte.baseSize, 2, YELLOW);
                        DrawTextureRec(zip, frameRec, zipPos, WHITE);
                        DrawTextureRec(Enemy, frameRecEnemy, enemyPos, GREEN);
                    }
                            if(dado == 4){
                        DrawTextEx(fonte, "Zip -30 de vida", (Vector2){ 110, 420}, (float)fonte.baseSize, 2, YELLOW);
                        DrawTextEx(fonte, "Bug +8 de vida", (Vector2){110, 450}, (float)fonte.baseSize, 2, YELLOW);
                        DrawTextureRec(zip, frameRec, zipPos, WHITE);
                        DrawTextureRec(Enemy, frameRecEnemy, enemyPos, GREEN);
                    }

        }break;

        case DEFEAT:
        {  
            UnloadTexture(Enemy);
            UnloadTexture(zip);
            UnloadTexture(background);
            ClearBackground(BLACK);
            UnloadFont(fonte);  
            DrawText(TextFormat("Voce morreu"), 200, 180, 80, RED);
        }break;
        
        case WIN:
        {
            UnloadTexture(Enemy);
            UnloadTexture(zip);
            ClearBackground(RAYWHITE);
            UnloadTexture(background);
            UnloadFont(fonte); 
            DrawText(TextFormat("Voce venceu"), 200, 180, 80, VIOLET);
        }break;
        
    }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void cria(Pilha *s){

    s->topo = NULL;
    s->tamPilha = 0;

}

int empilha(Pilha *s, int dado){

    No *aux;
    aux = (No *) malloc(sizeof(No));
    if(aux == NULL)
        return 0;

    aux->dado = dado;
    aux->prox = s->topo;
    s->topo = aux;
    s->tamPilha++;

    return 1;
}

int desempilha(Pilha *s, int *dado){

    No *aux = s->topo;
    if (aux == NULL)
        return 0;

    *dado = aux->dado;
    s->topo = aux->prox;
    s->tamPilha--;
    free(aux);

    return 1;
}

/* void mostra(Pilha s){

    No *aux = s.topo;
    if(aux == NULL)
        printf("Pilha vazia...\n");
    else {

        while(aux != NULL){
            printf("Dado armazenado: %d\n", aux->dado);
            aux = aux->prox;
        }
    }
} */