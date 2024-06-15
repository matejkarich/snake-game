#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameFinished = false;
int windWidth = 40, windHeight=30;
int snakeX, snakeY, foodX, foodY;
int tailX[1000], tailY[1000];
enum movement {up, down, left, right};
movement move;
int snakeSize;
int score;

//function that constructs the borders and elements of game
void board() {
    system("cls");
    for (int i = 0; i < windHeight; i++) {
        for (int j = 0; j < windWidth; j++) {
            if (i == 0 || i == windHeight-1) {
                std::cout << "-";
            }   
            else if (j == 0 || j == windWidth-1) {
                std::cout << "-";
            }
            else if (i == snakeY && j == snakeX) {
                std::cout << "S";
            }
            else if (i == foodY && j == foodX) {
                std::cout << "O";
            }
            else {
                bool pass = false;
                for (int k = 0; k < snakeSize; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "s";
                        pass = true;
                    }
                }
                if (pass != true) {
                    std::cout << " "; 
                }      
            } 
        }
        std::cout << "" << std::endl;
    }
    std::cout << "Score: " << score << std::endl;
}

void control() {
    //takes keyboard input
    if (kbhit()) {
        switch (getch()) {
        case 'w':
            move = up;
            break;
        case 's':
            move = down;
            break;
        case 'a':
            move = left;
            break;
        case 'd':
            move = right;
            break; 
        case 'q':
            gameFinished = true;
            break;
        default:
            break;
        }
    } 
    //determines the snake tail and the appropriate coordinates
    for (int i = snakeSize; i > 0; i--) {
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }
    tailX[0] = snakeX;
    tailY[0] = snakeY;
    //takes the input to set the new movement direction
    switch (move) {
        case up:
            snakeY--;
            break;
        case down:
            snakeY++;
            break;
        case left:
            snakeX--;
            break;
        case right:
            snakeX++;
            break;
        default:
            break;
    }
    //increases score and snake whenever food is consumed
    if (snakeX == foodX && snakeY == foodY) {
        foodX = rand() % (windWidth-2)+1;
        foodY = rand() % (windHeight-2)+1;
        score++;
        snakeSize++;
	}
    //ends the game if the snake runs into a wall
    if (snakeX <= 0 || snakeX >= windWidth-1) {
        gameFinished = true;
    }
    else if (snakeY <= 0 || snakeY >= windHeight-1) {
        gameFinished = true;
    }
    //ends the game if the snake touches its tail
    for (int element = 0; element < snakeSize; element++) {
        if (tailX[element] == snakeX && tailY[element] == snakeY) {
            gameFinished = true;
        }
    }  
}

int main() {
    score = 0;
    snakeSize = 0;
    snakeX = windWidth/2;
    snakeY = windHeight/2;
    foodX = rand() % (windWidth-2) + 1;
    foodY = rand() % (windHeight-2) + 1;
    while (gameFinished != true) {
        board();
        control();
        Sleep(30);
    }
}