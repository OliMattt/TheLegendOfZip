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

#ifndef ZIP_H
#define ZIP_H

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




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

    // Struct No Lista do Inventario

} No;

typedef struct
{
    No *inicio;
    No *fim;
    int tam;

    // Struct lista

} Lista;

typedef struct
{
    int Life;
    int level;
    char name[20];

    // struct save game

} SaveData;

// SAlva e carrega jogo
void SaveGame(const SaveData *data, const char *filename);
SaveData LoadGame(const char *filename);

// Manipulacao Lista Inventario
void cria(Lista *l);
int insere(Lista *l, int id, int quantidade, const char *descricao, const char *nome);
int retira(Lista *l, int id);
int estaVazia(Lista l);

// Desenha Menu de Inventario
void janelaMenu(int *seleciona, Lista l);

// Desenha telas
void drawExit(Texture2D buttonYes, Texture2D buttonNo, bool collision4, bool collision5, Color *cor, int btnAction);
void drawCredits(Texture2D buttonBack, bool collision6, Color *cor, int btnAction, Rectangle Button4);
void drawMenu(Rectangle Button1, Rectangle Button2, Rectangle Button3, Texture2D buttonNew, Texture2D buttonExit, Texture2D buttonCred, bool collision1, bool collision2, bool collision3, int btnAction, Color *cor);


#endif