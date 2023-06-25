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