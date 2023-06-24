#include <stdio.h>
#include <raylib.h>

typedef struct {
    const char* name;
    int health;
    int damage;
} Character;

void DrawBattleInfo(Character player, Character enemy)
{
    // Desenha as informações de batalha na janela
    DrawText("Batalha de RPG", 10, 10, 20, WHITE);
    DrawText("Jogador", 10, 50, 20, WHITE);
    DrawText(player.name, 10, 80, 20, WHITE);
    DrawText(TextFormat("Vida: %d", player.health), 10, 110, 20, WHITE);
    DrawText(TextFormat("Dano: %d", player.damage), 10, 140, 20, WHITE);

    DrawText("Inimigo", 400, 50, 20, WHITE);
    DrawText(enemy.name, 400, 80, 20, WHITE);
    DrawText(TextFormat("Vida: %d", enemy.health), 400, 110, 20, WHITE);
    DrawText(TextFormat("Dano: %d", enemy.damage), 400, 140, 20, WHITE);
}

void Battle(Character* player, Character* enemy)
{
    // Simula uma batalha simples
    while (player->health > 0 && enemy->health > 0)
    {
        // Atualiza a janela de renderização
        BeginDrawing();
        ClearBackground(BLACK);

        DrawBattleInfo(*player, *enemy);

        EndDrawing();

        // Processa a entrada do jogador
        if (IsKeyPressed(KEY_SPACE))
        {
            // O jogador ataca o inimigo
            enemy->health -= player->damage;

            // O inimigo ataca o jogador
            player->health -= enemy->damage;
        }
    }

    // Verifica o resultado da batalha
    if (player->health <= 0)
        printf("Você foi derrotado!\n");
    else if (enemy->health <= 0)
        printf("Você venceu!\n");
}

int main()
{
    // Configuração da janela
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Sistema de Batalha de RPG");

    // Criação dos personagens
    Character player = { "Jogador", 100, 20 };
    Character enemy = { "Inimigo", 80, 15 };

    SetTargetFPS(60);

    // Inicia a batalha
    Battle(&player, &enemy);

    CloseWindow();

    return 0;
}
