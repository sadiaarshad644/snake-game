#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y)
{
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void boundary()
{
    // Top border
    printf("%c", 218);
    for (int i = 1; i < 119; i++)
        printf("%c", 196);
    printf("%c", 191);

    // Side borders
    for (int i = 1; i < 29; i++)
    {
        gotoxy(119, i);
        printf("%c", 179);
        gotoxy(0, i);
        printf("%c", 179);
    }

    // Bottom border
    gotoxy(0, 29);
    printf("%c", 192);
    for (int i = 1; i < 119; i++)
        printf("%c", 196);
    printf("%c", 217);
}

void showScore(int len)
{
    gotoxy(50, 0);
    printf("Score: %d", len - 1);
}

void move(int *x, int *y, char *lastDir, char currentDir, int len)
{
    // Clear tail
    gotoxy(x[len - 1], y[len - 1]);
    printf(" ");

    // Move body segments
    for (int i = len - 1; i > 0; i--)
    {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    *lastDir = currentDir;
    
    // Draw body
    for (int i = 1; i < len; i++)
    {
        gotoxy(x[i], y[i]);
        printf("o");
    }
}

int checkDotCollision(int px, int py, int *x, int *y, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (px == x[i] && py == y[i])
            return 1;
    }
    return 0;
}

void gameOver(int x, int y, int len)
{
    gotoxy(x, y);
    printf("X"); // Head collision marker
    gotoxy(50, 15);
    printf("Game Over! Final Score: %d", len - 1);
    gotoxy(50, 16);
    printf("Press Enter to exit...");
    while (getch() != 13)
        ;
    exit(0);
}

void placeDot(int *px, int *py, int *x, int *y, int len)
{
    do
    {
        *py = (rand() % 28) + 1;
        *px = ((rand() % 58) * 2) + 3;
    } while (checkDotCollision(*px, *py, x, y, len));
    
    gotoxy(*px, *py);
    printf("*"); // Changed food symbol to asterisk for better visibility
}

int main()
{
    // Initialize game
    system("cls");
    boundary();
    
    // Game instructions
    gotoxy(1, 1);
    printf("- X --- X --- X --- X --- X --- X --- X --- X --- X --- SNAKES --- X --- X --- X --- X --- X --- X --- X --- X --- X -");
    gotoxy(1, 2);
    printf("%cUse arrow keys to move the snake", 179);
    gotoxy(1, 3);
    printf("%cBackward movement is not allowed", 179);
    gotoxy(1, 4);
    printf("%cPress Enter any time to end the game", 179);
    gotoxy(1, 5);
    printf("%cDon't maximize the window", 179);
    gotoxy(1, 6);
    printf("%cPress any key to continue", 179);
    
    getch();
    system("cls");
    boundary();
    showScore(1);

    // Game setup
    srand(time(NULL));
    int *x, *y, dotX, dotY, len = 1;
    char currentDir = 0, lastDir = 0;
    clock_t timer;

    // Allocate memory for snake segments
    x = (int *)malloc(sizeof(int) * (len + 1));
    y = (int *)malloc(sizeof(int) * (len + 1));
    x[0] = 25; // Initial head position
    y[0] = 15;

    // Place initial food
    placeDot(&dotX, &dotY, x, y, len);

    // Draw initial snake
    gotoxy(x[0], y[0]);
    printf("O");

    // Main game loop
    while (1)
    {
        // Input handling
        if (kbhit())
        {
            currentDir = getch();
            if (currentDir == 0 || currentDir == 224) // Extended key
                currentDir = getch();
                
            // Prevent reverse direction
            if ((currentDir == 75 && lastDir == 77) || // Left vs Right
                (currentDir == 77 && lastDir == 75) || // Right vs Left
                (currentDir == 72 && lastDir == 80) || // Up vs Down
                (currentDir == 80 && lastDir == 72))   // Down vs Up
            {
                currentDir = lastDir;
            }
        }

        // Movement delay
        timer = clock();
        while (clock() < timer + 250)
            ;
        
        // Handle movement
        switch (currentDir)
        {
            case 72: // Up
                move(x, y, &lastDir, currentDir, len);
                gotoxy(x[0], --y[0]);
                printf("^");
                if (y[0] == 0) gameOver(x[0], y[0], len);
                break;
                
            case 80: // Down
                move(x, y, &lastDir, currentDir, len);
                gotoxy(x[0], ++y[0]);
                printf("v");
                if (y[0] == 29) gameOver(x[0], y[0], len);
                break;
                
            case 75: // Left
                move(x, y, &lastDir, currentDir, len);
                gotoxy(x[0] -= 2, y[0]);
                printf("<");
                if (x[0] == 1) gameOver(x[0], y[0], len);
                break;
                
            case 77: // Right
                move(x, y, &lastDir, currentDir, len);
                gotoxy(x[0] += 2, y[0]);
                printf(">");
                if (x[0] == 119) gameOver(x[0], y[0], len);
                break;
                
            case 13: // Enter key to exit
                gameOver(x[0], y[0], len);
                break;
                
            default:
                break;
        }

        // Check self collision
        for (int i = 4; i < len; i++)
        {
            if (x[0] == x[i] && y[0] == y[i])
                gameOver(x[0], y[0], len);
        }

        // Check food collision
        if (x[0] == dotX && y[0] == dotY)
        {
            // Grow snake
            len++;
            x = (int *)realloc(x, sizeof(int) * (len + 1));
            y = (int *)realloc(y, sizeof(int) * (len + 1));
            
            // Place new food
            placeDot(&dotX, &dotY, x, y, len);
            
            // Update score
            showScore(len);
        }
    }

    free(x);
    free(y);
    return 0;
}