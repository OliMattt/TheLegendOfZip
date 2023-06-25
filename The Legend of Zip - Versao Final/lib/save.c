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

//--------------------------------------------------------------------------------------------------------------------
// Save Game

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