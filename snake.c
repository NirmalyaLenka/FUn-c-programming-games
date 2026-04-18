#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

int x, y, fruitX, fruitY, score, highScore;
int tailX[100], tailY[100];
int nTail;
int speed = 100;

enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
enum direction dir;

int gameOver;
int paused = 0;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void loadHighScore() {
    FILE *f = fopen("highscore.txt", "r");
    if(f == NULL) highScore = 0;
    else {
        fscanf(f, "%d", &highScore);
        fclose(f);
    }
}

void saveHighScore() {
    if(score > highScore) {
        FILE *f = fopen("highscore.txt", "w");
        fprintf(f, "%d", score);
        fclose(f);
    }
}

void Setup() {
    gameOver = 0;
    dir = STOP;

    x = WIDTH / 2;
    y = HEIGHT / 2;

    srand(time(0));
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;

    score = 0;
    nTail = 0;

    loadHighScore();
}

void Draw() {
    gotoxy(0,0);

    color(10);
    for(int i=0;i<WIDTH+2;i++) printf("#");
    printf("\n");

    for(int i=0;i<HEIGHT;i++) {
        for(int j=0;j<WIDTH;j++) {

            if(j==0) printf("#");

            if(i==y && j==x) {
                color(14);
                printf("O");
            }

            else if(i==fruitY && j==fruitX) {
                color(12);
                printf("@");
            }

            else {
                int print=0;
                for(int k=0;k<nTail;k++) {
                    if(tailX[k]==j && tailY[k]==i) {
                        color(11);
                        printf("o");
                        print=1;
                    }
                }

                if(!print) printf(" ");
            }

            if(j==WIDTH-1) {
                color(10);
                printf("#");
            }
        }
        printf("\n");
    }

    for(int i=0;i<WIDTH+2;i++) printf("#");

    color(15);
    printf("\nScore: %d",score);
    printf("\nHigh Score: %d",highScore);
    printf("\nSpeed: %d", 110-speed);
    printf("\nControls: WASD | P Pause | X Exit");
}

void Input() {
    if(_kbhit()) {
        switch(_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'p': paused = !paused; break;
            case 'x': gameOver = 1; break;
        }
    }
}

void Logic() {

    if(paused) return;

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for(int i=1;i<nTail;i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }

    // Wall collision
    if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = 1;

    // Self collision
    for(int i=0;i<nTail;i++)
        if(tailX[i]==x && tailY[i]==y)
            gameOver=1;

    // Fruit collision
    if(x==fruitX && y==fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;

        if(speed > 20)
            speed -= 2;
    }
}

int main() {

    Setup();

    while(!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(speed);
    }

    saveHighScore();

    color(12);
    printf("\n\nGame Over!");
    printf("\nFinal Score: %d", score);

    color(15);

    return 0;
}
