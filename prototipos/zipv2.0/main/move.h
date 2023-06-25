float gatoX = 100;
float gatoY = 100;

float enemyX = 200;
float enemyY = 200;

void movInim(void)
{
    if (IsKeyDown(KEY_D))
        enemyX += 5;
    if (IsKeyDown(KEY_A))
        enemyX -= 5;
    if (IsKeyDown(KEY_S))
        enemyY += 5;
    if (IsKeyDown(KEY_W))
        enemyY -= 5;
    return;
}