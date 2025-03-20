#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct
{
    int x;
    int y;
} Position;

char prompt(void);
void print_grid(int g[10][10]);
void print_pos(int x, int y);
bool GameOver(int g[10][10]);

int main(void)
{
    int grid[10][10] = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    Position pos;
    pos.x = 0;
    pos.y = 0;
    printf("\e[1;1H\e[2J");

    srand(time(0));
    int rndm = rand() % 6 + 1;
    for (int i = 0; i < rndm; i++)
    {
        int y;
        int x;

        x = rand() % 10 + 1;
        y = rand() % 10 + 1;

        grid[y][x] = 3;
    }
    print_grid(grid);
    while (true)
    {
        print_pos(pos.x, pos.y);
        char m = prompt();
        grid[pos.y][pos.x] = 0;
        if (m == 'd')
        {
            pos.x += 1;
            if (pos.x == 10)
            {
                pos.x = 0;
                pos.y += 1;
            }
        }
        if (m == 'a')
        {
            pos.x -= 1;
            if (pos.x == -1)
            {
                pos.x = 0;
                pos.y -= 1;
            }
        }
        if (m == 'w')
        {
            pos.y -= 1;
        }
        if (m == 's')
        {
            pos.y += 1;
        }
        grid[pos.y][pos.x] = 1;
        printf("\e[1;1H\e[2J");
        // Check if player went out of bounds
        if (pos.y < 0 || pos.y > 10)
        {
            printf("\e[1;1H\e[2J");
            printf("Player went out of bounds!");
            return 1;
        }
        // Move enemies
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {

                if (grid[i][j] == 3)
                {

                    int dir = (rand() % 4) + 1;

                    if (dir == 1)
                    {
                        grid[i][j] = 0;
                        grid[i + 1][j] = 3;
                    }
                    if (dir == 2)
                    {
                        grid[i][j] = 0;
                        grid[i - 1][j] = 3;
                    }
                    if (dir == 3)
                    {
                        grid[i][j] = 0;
                        grid[i][j + 1] = 3;
                    }
                    if (dir == 4)
                    {
                        grid[i][j] = 0;
                        grid[i][j - 1] = 3;
                    }
                };
            }
        }
        // Check if enemy collided with player
        if (GameOver(grid) == true)
        {
            printf("You got eaten!");
            return 1;
        }
        print_grid(grid);
    }
}

char prompt(void)
{
    char move[10];

    while (true)
    {
        printf("Where do you want to move (w/a/s/d/n): \n");
        scanf("%9s", move);

        if (strlen(move) == 1 && (move[0] == 'w' || move[0] == 'a' || move[0] == 's' || move[0] == 'd' || move[0] == 'n'))
        {
            return move[0];
        }

        while (getchar() != '\n')
            ;
    }
}

void print_grid(int g[10][10])
{
    printf("\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%i", g[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void print_pos(int x, int y)
{
    printf("Player's current position: \n");
    printf("X: %i\n", x);
    printf("Y: %i\n", y);
}
bool GameOver(int g[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (g[i][j] == 1)
            {
                return false;
            }
        }
    }
    return true;
}