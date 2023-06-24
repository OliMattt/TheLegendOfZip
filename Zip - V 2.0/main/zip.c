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

    Nosso código foi separado em dois, devido ao pouco tempo de produção
    Um exibe o mapa, as animações, a câmera e o movimento do Zip
    O segundo exibe nosso protótipo de batalha

********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "move.h"

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

#define zip_width           384
#define zip_height          128 

#define ZIPBLUE             (Color){108,185,201,255}

// float gatoX = 100;
// float gatoY = 100;

// float enemyX = 200;
// float enemyY = 200;

Rectangle ButtonExitYes = {244, 300, 122, 25};
Rectangle ButtonExitNo = {456, 300, 112, 25};

typedef enum MenuScreen
{
    LOGO,
    MENU,
    CREDITS,
    EXIT,
} MenuScreen;

typedef struct no
{
    int id, quantidade;
    char *descricao;
    char *nome;
    struct no *ant;
    struct no *prox;
} No;

typedef struct
{
    No *inicio;
    No *fim;
    int tam;
} Lista;

typedef struct
{
    int Life;
    int level;
    char name[20];
} SaveData;

void SaveGame(const SaveData *data, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file != NULL)
    {
        fwrite(data, sizeof(SaveData), 1, file);
        fclose(file);
        printf("SaveGame: %s saved successfully!\n", filename);
    }
    else
    {
        printf("SaveGame: Failed to save %s\n", filename);
    }
}

SaveData LoadGame(const char *filename)
{
    SaveData data;
    FILE *file = fopen(filename, "rb");
    if (file != NULL)
    {
        fread(&data, sizeof(SaveData), 1, file);
        fclose(file);
        printf("LoadGame: %s loaded successfully!\n", filename);
    }
    else
    {
        printf("LoadGame: Failed to load %s\n", filename);
    }
    return data;
}

void cria(Lista *l);
int insere(Lista *l, int id, int quantidade, const char *descricao, const char *nome);
int retira(Lista *l, int id);
int estaVazia(Lista l);

void moveBola(Vector2 *ballPosition);
void janelaPrincipal(Vector2 ballPosition);
void janelaMenu(int *seleciona, Lista l);

void drawExit(Texture2D buttonYes, Texture2D buttonNo, bool collision4, bool collision5, Color *cor, int btnAction);
void drawCredits(Texture2D buttonBack, bool collision6, Color *cor, int btnAction, Rectangle Button4);
void drawMenu(Rectangle Button1, Rectangle Button2, Rectangle Button3, Texture2D buttonNew, Texture2D buttonExit, Texture2D buttonCred, bool collision1, bool collision2, bool collision3, int btnAction, Color *cor);

int main(void)
{

    // Texture2D background = LoadTexture("resources/mapa1.png");

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

    InitWindow(screenWidth, screenHeight, "The Legend of Zip");
    InitAudioDevice();

    // Declaração de sons
    Sound newgame = LoadSound("resources/newgame.wav");
    Sound creditos = LoadSound("resources/creditos.wav");
    Sound return1 = LoadSound("resources/return.wav");
    Sound exit = LoadSound("resources/exit.wav");
    Sound back = LoadSound("resources/back.wav");
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

    Color cor;
    bool menu = false;
    int seleciona = 0;
    Lista l;

    cria(&l);
    insere(&l, 103, 3, "apenas um item", "item 1");
    insere(&l, 244, 8, "apenas um item", "item 2");
    insere(&l, 399, 5, "apenas um item", "item 3");
    insere(&l, 415, 7, "apenas um item", "item 4");

    //------------------------------------------------------------------------

    const char msg1[50] = "Press ENTER or CLICK to Continue!";
    const char msg2[50] = "Are you sure?";
    const char msg3[256] = {"Gameplay and Art - Giulia \n Combat and Art - Mateus \n Main Menu and Battle Menu - Yuri"};

    Vector2 mousePoint = {0.0f, 0.0f};
    Vector2 fontPos = {screenWidth / 2.0f - MeasureTextEx(fonte, msg1, 20, 2).x / 2, screenHeight / 1.5f + 100};
    Vector2 fontPos2 = {screenWidth / 2.0f - MeasureTextEx(fonte, msg2, 20, 2).x / 2, screenHeight / 2.0f - 100};
    Vector2 fontPos3 = {screenWidth / 2.0f - MeasureTextEx(fonte, msg3, 30, 2).x / 2, screenHeight / 2.0f - 100};

    MenuScreen CurrentScreen = LOGO;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // enquanto a janela nao fechar
    while (!WindowShouldClose())
    {
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
        case LOGO:
        {
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER) || IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                CurrentScreen = MENU;
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
                    bool Paused = false;

                        Texture2D background = LoadTexture("resources/mapa1.png");
                        Texture2D zip = LoadTexture("resources/zip11.png");        // Texture loading
                        Texture2D up = LoadTexture("resources/up.png");
                        Texture2D down = LoadTexture("resources/down.png");
                        Texture2D left = LoadTexture("resources/left.png");
                        Texture2D right = LoadTexture("resources/right.png"); // Texture loading

                    // Inicia o mapa na posiçao 0.0 e define sua velocidade
                    Vector2 mapPos = {0.0, 0.0};
                    float speed = 5.0;

// Vetor de posição do gato
    Vector2 zipPos = {
        (float)screenWidth/2.0f - 4.0f * (0.5f * (float)zip_width/7.0f),
        (float)screenHeight/2.0f - 4.0f * (0.5f * (float)zip_height)
    };

                    // Vetor de posição da animação parada
                    // Retângulo que delimita o frame apresentado
                    // Inicia no frame 0
                    Vector2 position = {350.0f, 280.0f};
                    Rectangle frameRec = {0.0f, 0.0f, (float)zip.width / 6, (float)zip.height};
                    int currentFrame = 0;

                    // Contador e Velocidade de frame (por segundo)
                    int framesCounter = 0;
                    int framesSpeed = 8; // Number of spritesheet frames shown by second

                    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
                    //--------------------------------------------------------------------------------------

                    // Enquanto a janela de jogo não fechar, o código não é executado
                    while (!WindowShouldClose()) // Detect window close button or ESC key
                    {
                        // Update
                        //----------------------------------------------------------------------------------
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

                        if (!Paused && !menu)
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

                        DrawText(TextFormat("%s", gameData.name), 10, 10, 30, BLACK);
                        DrawText(TextFormat("HP: %d", gameData.Life), 100, 10, 20, BLACK);
                        DrawText(TextFormat("Level: %d", gameData.level), 200, 10, 20, BLACK);

                        if (Paused && !menu)
                        {
                            DrawText("Paused", 600, 380, 40, GREEN);
                        }

                        if (menu)
                        {
                            BeginDrawing();
                            ClearBackground(WHITE);
                            janelaMenu(&seleciona, l);
                            EndDrawing();
                        }

                        

                        EndDrawing();

                        //----------------------------------------------------------------------------------
                    }

                    // De-Initialization
                    //--------------------------------------------------------------------------------------
                    UnloadTexture(zip); // Texture unloading

                    return 1;
                }
            }

            if (collision2)
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

            if (collision3)
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
        {
            DrawTexture(logo, 0, 0, WHITE);
            DrawTextEx(fonte, msg1, fontPos, 20, 2, GREEN);
        }
        break;

        case MENU:
        {
            DrawTexture(menu1, 5, 2.5, WHITE);
            drawMenu(Button1, Button2, Button3, buttonNew, buttonExit, buttonCred, collision1, collision2, collision3, btnAction, &cor);
        }
        break;

        case CREDITS:
        {
            ClearBackground(RAYWHITE);
            DrawTextEx(fonte, msg3, fontPos3, 25, 2, VIOLET);
            drawCredits(buttonBack, collision6, &cor, btnAction, Button4);
        }
        break;

        case EXIT:
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

    CloseWindow();
    CloseAudioDevice();
    //--------------------------------------------------------------------------------------

    return 0;
}
// void movInim(void)
// {
    // if (IsKeyDown(KEY_D))
        // enemyX += 5;
    // if (IsKeyDown(KEY_A))
        // enemyX -= 5;
    // if (IsKeyDown(KEY_S))
        // enemyY += 5;
    // if (IsKeyDown(KEY_W))
        // enemyY -= 5;
    // return;
// }

void cria(Lista *l)
{
    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;
}

int insere(Lista *l, int id, int quantidade, const char *descricao, const char *nome)
{

    // alocando na memoria
    No *aux = (No *)malloc(sizeof(No));
    if (aux == NULL)
        return 0;

    // guarda o dado
    aux->id = id;
    aux->quantidade = quantidade;
    aux->quantidade = quantidade;

    // passa valores string para aux descricao e aux nome
    aux->descricao = (char *)malloc(strlen(descricao) + 1); // Aloca memória para descricao
    strcpy(aux->descricao, descricao);
    aux->nome = (char *)malloc(strlen(nome) + 1); // Aloca memória para nome
    strcpy(aux->nome, nome);
    l->tam++;

    // primeiro elemento
    if (l->inicio == NULL)
    {

        l->inicio = aux;
        l->fim = aux;
        aux->ant = NULL;
        aux->prox = NULL;

        return 1;
    }

    // insere no fim

    aux->ant = l->fim;
    aux->prox = NULL;
    l->fim->prox = aux;
    l->fim = aux;
    l->inicio->ant = l->fim;

    return 1;
}

int estaVazia(Lista l)
{

    if (l.inicio == NULL)
        return 1;

    return 0;
}

int retira(Lista *l, int id)
{

    No *aux;

    if (l->inicio == NULL)
    {
        printf("Lista vazia\n");
        return 0;
    }

    /*lista unitaria */
    if ((id == l->inicio->id) && (l->inicio == l->fim))
    {
        aux = l->inicio;
        l->inicio = NULL;
        l->fim = NULL;
        free(aux->descricao); // libera memória alocada para descricao
        free(aux->nome);      // libera memória alocada para nome
        free(aux);
        l->tam--;

        return 1;
    }

    /*remove primeiro item */
    if (id == l->inicio->id)
    {
        aux = l->inicio;
        l->inicio = aux->prox;
        l->inicio->ant = l->fim;
        l->fim->prox = l->inicio;
        free(aux->descricao);
        free(aux->nome);
        free(aux);
        l->tam--;

        return 1;
    }

    /*remove ultimo item */
    if (id == l->fim->id)
    {
        aux = l->fim;
        l->fim = aux->ant;
        l->fim->prox = l->inicio;
        l->inicio->ant = l->fim;
        free(aux->descricao);
        free(aux->nome);
        free(aux);
        l->tam--;

        return 1;
    }

    /*remove um item do meio */
    aux = l->inicio->prox;

    // percorre a lista ate achar o elemento, ou chegar no fim
    while ((id != aux->id) && (aux != l->fim))
        aux = aux->prox;

    if (aux == l->fim)
    { // elemento nao encontrado
        printf("O elemento %d nao esta na lista.\n", id);
        return 0;
    }

    // remove elemento
    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;
    free(aux->descricao);
    free(aux->nome);
    free(aux);
    l->tam--;

    return 1;
}

void janelaMenu(int *seleciona, Lista l)
{

    static No *aux = NULL; // Declaração da variável aux como estática, nao reinicia para cada vez que a funcao e chamada

    char texto[5];
    int pagMax = l.tam;

    if (aux == NULL)
    {
        aux = l.inicio; // Inicializa aux na primeira chamada da função
    }

    ClearBackground(RAYWHITE);
    DrawText("Inventario", 50, 60, 20, BLACK);

    // desenha retangulo na tela
    DrawRectangleLines(50, 80, 700, 350, BLACK);

    // snprintf le um int e transforma em string
    snprintf(texto, sizeof(texto), "%d", ((*seleciona) + 1));
    DrawText(texto, 170, 60, 20, BLACK);
    DrawText("/", 185, 60, 20, BLACK);
    snprintf(texto, sizeof(texto), "%d", pagMax);
    DrawText(texto, 205, 60, 20, BLACK);

    DrawText(aux->nome, 70, 100, 20, BLACK);

    DrawText("Id:", 200, 100, 20, BLACK);
    snprintf(texto, sizeof(texto), "%d", aux->id);
    DrawText(texto, 230, 100, 20, BLACK);

    DrawText("Quantidade:", 70, 150, 20, BLACK);
    snprintf(texto, sizeof(texto), "%d", aux->quantidade);
    DrawText(texto, 200, 150, 20, BLACK);

    DrawText("Descricao:", 70, 220, 20, BLACK);
    DrawText(aux->descricao, 70, 250, 20, BLACK);

    // informacoes da interface
    DrawText("-> Proxima pagina", 50, 450, 20, BLACK);
    DrawText("<- Pagina Anterior", 50, 480, 20, BLACK);
    DrawText("Sair (Q)", 650, 450, 20, BLACK);

    // seleciona o item no menu
    if ((IsKeyPressed(KEY_RIGHT)) && (*seleciona < l.tam) && (aux->prox != NULL))
    {
        (*seleciona)++;
        aux = aux->prox;
    }
    if ((IsKeyPressed(KEY_LEFT)) && (*seleciona > 0) && (aux->ant != NULL))
    {
        (*seleciona)--;
        aux = aux->ant;
    }
}

//*********************************************************************************************************

void drawExit(Texture2D buttonYes, Texture2D buttonNo, bool collision4, bool collision5, Color *cor, int btnAction)
{

    if (collision4)
    {
        *cor = YELLOW;

        if (btnAction == 1)
        {
            *cor = RED;
        }
    }
    else
    {
        *cor = WHITE;
    }
    DrawRectangleRec(ButtonExitYes, BLANK);
    DrawTexture(buttonYes, 244, 300, *cor);

    if (collision5)
    {
        *cor = YELLOW;

        if (btnAction == 2)
        {
            *cor = RED;
        }
    }
    else
    {
        *cor = WHITE;
    }
    DrawRectangleRec(ButtonExitNo, BLANK);
    DrawTexture(buttonNo, 456, 300, *cor);
}

void drawCredits(Texture2D buttonBack, bool collision6, Color *cor, int btnAction, Rectangle Button4)
{
    if (collision6)
    {
        *cor = YELLOW;
        if (btnAction == 2)
            *cor = RED;
    }
    else
        *cor = WHITE;

    DrawRectangleRec(Button4, BLANK);
    DrawTexture(buttonBack, 344, 350, *cor);
}

void drawMenu(Rectangle Button1, Rectangle Button2, Rectangle Button3, Texture2D buttonNew, Texture2D buttonExit, Texture2D buttonCred, bool collision1, bool collision2, bool collision3, int btnAction, Color *cor)
{

    if (collision1)
    {
        *cor = YELLOW;

        if (btnAction == 1)
        {
            *cor = RED;
        }
    }
    else
    {
        *cor = WHITE;
    }
    DrawRectangleRec(Button1, BLANK);
    DrawTexture(buttonNew, 144, 100, *cor);

    if (collision2)
    {
        *cor = YELLOW;

        if (btnAction == 2)
        {
            *cor = RED;
        }
    }
    else
    {
        *cor = WHITE;
    }
    DrawRectangleRec(Button2, BLANK);
    DrawTexture(buttonCred, 144, 150, *cor);

    if (collision3)
    {
        *cor = YELLOW;

        if (btnAction == 3)
        {
            *cor = RED;
        }
    }
    else
    {
        *cor = WHITE;
    }
    DrawRectangleRec(Button3, BLANK);
    DrawTexture(buttonExit, 144, 200, *cor);
}