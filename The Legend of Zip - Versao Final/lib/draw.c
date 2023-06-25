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

#include "../include/zip.h"

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


    Rectangle ButtonExitYes = {244, 300, 122, 25};
    Rectangle ButtonExitNo = {456, 300, 112, 25};

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
