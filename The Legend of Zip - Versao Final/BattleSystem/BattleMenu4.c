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

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "raylib.h"

typedef enum BattleScreen { MENU, MAGIC1, MAGIC2, HEAL, RUN, WIN, DEFEAT, ENEMYATACK } BattleScreen;

//structs com informação de vida e de dano dos inimigos e do Zip
struct Enemy_Status {

    int vida;
    int dano_base;

};

struct Zip_Status {

    int vidaZip;
    int DMG_Base;
};

//struct para modificar a vida e o dano dado pelo Zip
struct Modificadores {

    int modificadorDMG, modificadorVida;

};

//struct de pilha
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

//------------------------------------------------------------------------------------

int main(void)
{
    //Declaração dos modificadores baseados em qual tipo de inimigo eles são. 
    //struct Enemy_Status EnemyTutorial = {25, 3};
    //struct Enemy_Status EnemyLow = {35, 5};
    //struct Enemy_Status EnemyMid = {50, 7};
    //struct Modificadores ModTutorial = {0, -3};
    //struct Modificadores ModLow = {1, 2};
    //struct Modificadores ModHigh = {4, 6};
    // struct Modificadores ModBOSS = {8, 15};

    struct Enemy_Status EnemyBOSS = {200, 15};  //declara a vida e dano base do boss
    struct Zip_Status Zip = {200, 10}; //declara a vida e dano base do Zip
    struct Modificadores ModMid = {2, 4}; //declara os modificadores de dano
    
    // Inicialização
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    //Funcoes de pilha----------------------

        
    
    Pilha s;
    int dado;
    srand(time(NULL));

    cria(&s);
    
    for(int i=0; i < 1000; i++){
        dado = rand() %4;
        empilha(&s, dado);
        }
    // Pilha é utilizada para randomizar os ataques inimigo, no comeo da batalha são empilhados 1000 valores entre 0 e 3
    //-------------------------------------

    InitWindow(screenWidth, screenHeight, "Battle Menu"); //inicia a janela
    
    InitAudioDevice();  //inicia dispositivo de audio
    Music music = LoadMusicStream("resources/Music.mp3"); //carrega a musica
    PlayMusicStream(music); //toca a musica
    
    //Carrega as texturas utilizadas para o Zip, inimigo e Background
    Texture2D Enemy = LoadTexture("resources/bug1.png");
    Texture2D background = LoadTexture("resources/poke2.png");
    Texture2D zip = LoadTexture("resources/zip.png");
    
    Font fonte = LoadFontEx("resources/pixantiqua.ttf", 32, 0, 250); //carrega a fonte utilizada nos textos
    
    //Desenha os retangulos usados para hitbox dos botões 
    Rectangle BattleMenu = {100, 400, 600, 150};
    Rectangle BattleMagic1 = {200, 425, 112, 25};
    Rectangle BattleMagic2 = {200, 500, 112, 25};
    Rectangle BattleHeal = {500, 425, 112, 25};
    Rectangle BattleRun = {500, 500, 112, 25};
    Rectangle ButtonExitYes = {200, 475, 122, 25};
    Rectangle ButtonExitNo = {500, 475, 112, 25};
    
    
    bool click = false; //recebe o click do mouse
    bool release = false; //recebe o soltar do botão do mouse
    bool enter = false; //recebe enter
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

    
    int enemyLife = EnemyBOSS.vida; //variael para mostrar a vida do inimigo
    int heroLife = Zip.vidaZip; //variavel para mostrar a vida do Zip
    int magicLimit = 4; //variavel utilizada para limitar o numero de Magia 2 que pode ser utilizado.
    
    Vector2 mousePoint = { 0.0f, 0.0f }; //vetor para inicializar o ponteiro do mouse
    Vector2 mapPos={0.0, 0.0}; //vetor para inicializar a posição do mapa
    
    Vector2 zipPos = { 175.0f, 280.0f }; //vetor para determinar posição do zip na tela
    Vector2 enemyPos = { 450.0f, 155.0f }; //vetor para determinar posição do inimigo na tela
    Vector2 enemyAttackPos = { 175.0f, 155.0f }; //vetor para determinar posição do inimigo na tela durante o ataque

    //parametros necessarios para desenhar as texturas usando o DrawTextureEx 
    Rectangle frameRec = { 0.0f, 0.0f, (float)zip.width/6, (float)zip.height }; 
    Rectangle attack1 = { 0.0f, 0.0f, (float)zip.width, (float)zip.height };
    Rectangle frameRecEnemy = { 0.0f, 0.0f, (float)Enemy.width, (float)Enemy.height };
    

    BattleScreen CurrentBattleScreen = MENU; //incializa o menu de batalha no menu inicial
    
    //funções utilizadas para centralizar os textos de vitoria e derrota ao final do jogo
    const char msg1[50] = "Voce venceu!!";
    const char msg2[50] = "Voce Morreu!!";
    Vector2 fontPos = {screenWidth/2.0f - MeasureTextEx(fonte, msg1, 60, 2).x/2, screenHeight/2.0f - 50}; //subtrai a largura da tela pela metade do tamanho da mensagem para centralizar o texto
    
    SetTargetFPS(60);               
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Enquanto esc não for pressionado
    {
        mousePoint = GetMousePosition(); //mousepoint recebe posição do cursor do mouse
        click = IsMouseButtonDown(MOUSE_BUTTON_LEFT); //recebe se o botão do mouse foi pressionado
        release = IsMouseButtonReleased(MOUSE_BUTTON_LEFT); ///recebe se o botão do mouse foi solto
        collision1 = CheckCollisionPointRec(mousePoint, BattleMagic1); //checa colisão entre o cursor do mouse e os retangulos de hitbox
        collision2 = CheckCollisionPointRec(mousePoint, BattleMagic2);
        collision3 = CheckCollisionPointRec(mousePoint, BattleHeal);
        collision4 = CheckCollisionPointRec(mousePoint, BattleRun);
        collision5 = CheckCollisionPointRec(mousePoint, ButtonExitYes);   
        collision6 = CheckCollisionPointRec(mousePoint, ButtonExitNo); 
        
        UpdateMusicStream(music);
        
        
        
    //menu principal de batalha
    //cada if detecta se existe colisão do mouse com o botão, e se tiver colisão, detecta se há release do botão do mouse e se houver joga para outra tela 
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
            
            //vai para outra tela e sai da batalha caso a vida do zip ou do inimigo chegue em zero
            if(heroLife <= 0) 
            {
                    CurrentBattleScreen = DEFEAT;
            }
            if(enemyLife <= 0)
            {
                    CurrentBattleScreen = WIN;
            }
        }break;
        
        case MAGIC1: //tela de magia 
        {
           if(click){
               magicLimit ++;  //magiclimit é o limite de uso da magia 2. Cada uso da magia2 consome 2 e cada magia1 retorna 1, podem utilizar uma magia2 a cada duas magias1
               enemyLife = enemyLife - Zip.DMG_Base; //subtrai o dano base da vida do inimigo
               CurrentBattleScreen = ENEMYATACK; //passa o round pro inimigo
           }
        }break;
        
        case MAGIC2:
        {
           if(click){
               //se magic limit for maior que 2, executa a magia2, se não retorna pra seleção
               if(magicLimit >= 2){
                    enemyLife = enemyLife - (Zip.DMG_Base + ModMid.modificadorDMG);
                    magicLimit -= 2;
                    CurrentBattleScreen = ENEMYATACK;
               }
                else{
                    if(click)CurrentBattleScreen = MENU;
                }
           }
        }break;
        
        case HEAL:
        {
           if(click){
               heroLife = heroLife + 20; //cura o zip
               CurrentBattleScreen = ENEMYATACK;
           }
        }break;
        
        case RUN: //da a opção para o zip fugir da batalha
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
                    btnAction2 = true;
                }
                else if (release){
                    CurrentBattleScreen = MENU; 
                }
                else{
                    btnAction2 = false;
                }
            }  
        }break;
        case ENEMYATACK: //roud do inimigo
        {  
            if (release) //se ouver release do mouse executa as funções e troca de tela 
            {
                desempilha(&s, &dado); //desempilha um valor da pilha e usa ele para selecionar o que o nimigo vai executar no round dele
                    
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
                        enemyLife = enemyLife + 10;
                        CurrentBattleScreen = MENU;
                    }
                     if(dado == 4){
                        heroLife = heroLife - 8;
                        CurrentBattleScreen = MENU;
                        enemyLife = enemyLife + 8;
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

   
    // funções de desenho do menu de batalha
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);
    
    //utiliza mesmo switchcase do menu
    switch(CurrentBattleScreen) 
    {
        case MENU:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);//desenha o mapa
            DrawRectangleRec(BattleMenu, BLACK);
            DrawRectangleRec(BattleMagic1, BLANK);//desenha os botões transparentes de hitbox
            DrawRectangleRec(BattleMagic2, BLANK);
            DrawRectangleRec(BattleHeal, BLANK);
            DrawRectangleRec(BattleRun, BLANK);
            DrawTextureRec(Enemy, frameRecEnemy, enemyPos, WHITE); //desemja o inimigo
            DrawTextureRec(zip, frameRec, zipPos, WHITE); //desenha o zip
            DrawTextEx(fonte, TextFormat("%i", heroLife), (Vector2){ 10, 180}, 60, 2, DARKPURPLE); //escreve a vida do zip na tela
            DrawTextEx(fonte, TextFormat("%i", enemyLife), (Vector2){ 680, 180}, 60, 2, RED); //escreve a vida do inimigo na tela
          
            
            if (collision1){
                    DrawTextEx(fonte, "Magia 1", (Vector2){ 200, 425}, (float)fonte.baseSize, 2, YELLOW); //desenha o texto do botão em amarelo para desmostrar que o mouse está em cima dele

                    if(btnAction1){
                        DrawTextEx(fonte, "Magia 1", (Vector2){ 200, 425}, (float)fonte.baseSize, 2, GREEN); //desenha em verde para desmostrar o click. A tela é trocada ao soltar o botão
                    }
                }
            else{
                    DrawTextEx(fonte, "Magia 1", (Vector2){ 200, 425}, (float)fonte.baseSize, 2, DARKPURPLE);//desenha o botão desativado
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
        case MAGIC1: //redesenha a tela para demostrar o ataque utilizado pelo zip
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawRectangleRec(BattleMenu, BLACK);
            DrawTextEx(fonte, "Magia 1 utilizada!", (Vector2){ 110.0f, 420.0f}, (float)fonte.baseSize, 2, DARKPURPLE);
            DrawTextEx(fonte, TextFormat("%i de Dano", Zip.DMG_Base), (Vector2){ 110, 460}, (float)fonte.baseSize, 2, RED);
            DrawTextureRec(Enemy, frameRecEnemy, enemyPos, YELLOW);
            DrawTextureRec(zip, frameRec, zipPos, WHITE);
        }break;
        case MAGIC2: //se magiclimit for maior que 2 desenha o ataque, se não avisa que não teve ataque
        {
            if(magicLimit >= 2){
                DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
                DrawRectangleRec(BattleMenu, BLACK);
                DrawTextEx(fonte, "Magia 2 utilizada!", (Vector2){ 110.0f, 420.0f}, (float)fonte.baseSize, 2, DARKPURPLE);
                DrawTextEx(fonte, TextFormat("%i de Dano", (Zip.DMG_Base + ModMid.modificadorDMG)), (Vector2){ 110, 460}, (float)fonte.baseSize, 2, RED);
                DrawTextureRec(Enemy, frameRecEnemy, enemyPos, RED);
                DrawTextureRec(zip, attack1, zipPos, WHITE);
            }
            else{
                DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
                DrawRectangleRec(BattleMenu, BLACK);
                DrawTextEx(fonte, "Sem energia para Magia 2!!", (Vector2){ 110, 460}, (float)fonte.baseSize, 2, RED);
                DrawTextureRec(Enemy, frameRecEnemy, enemyPos, WHITE);
                DrawTextureRec(zip, frameRec, zipPos, WHITE); 
            }
        }break;
        
        case HEAL: //redesenha a tela para demostrar a cura 
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
                
                    DrawTextEx(fonte, "Sim", (Vector2){ 220, 475}, (float)fonte.baseSize, 2, YELLOW);
                    
                if(btnAction1){
                    
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
        
        case ENEMYATACK: //desenha os ataques inimigos
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
                        DrawTextEx(fonte, "LifeSteal: Zip -8 de vida", (Vector2){ 110, 420}, (float)fonte.baseSize, 2, YELLOW);
                        DrawTextEx(fonte, "Bug +8 de vida", (Vector2){110, 450}, (float)fonte.baseSize, 2, YELLOW);
                        DrawTextureRec(zip, frameRec, zipPos, WHITE);
                        DrawTextureRec(Enemy, frameRecEnemy, enemyPos, GREEN);
                    }

        }break;
        
        //desenha as telas de vitoria e derrota
        case DEFEAT:
        {  
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawTextEx(fonte, msg2, fontPos, 60, 2, RED);
            if (enter) //se tiver enter, descarrega as texturas e a musica da memoria
            {
                UnloadTexture(Enemy);
                UnloadTexture(zip);
                UnloadTexture(background);
                ClearBackground(BLACK);
                UnloadFont(fonte);
                UnloadMusicStream(music); 
            }
        }break;
        
        case WIN:
        {
            DrawTextureEx(background, mapPos, 0.0, 3.2, WHITE);
            DrawTextEx(fonte, msg1, fontPos, 60, 2, DARKPURPLE);
            
            if (enter)
            {
                UnloadTexture(Enemy);
                UnloadTexture(zip);
                ClearBackground(RAYWHITE);
                UnloadTexture(background);
                UnloadFont(fonte); 
                UnloadMusicStream(music); 
            }
        }break;
        
    }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}
//função para criar a pilha
void cria(Pilha *s){

    s->topo = NULL;
    s->tamPilha = 0;

}

//empilha os valores gerados
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

//desempilha os valores 

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
