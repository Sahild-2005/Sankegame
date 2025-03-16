#include <graphic.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LENGTH 100

struct Snake {
    int x[MAX_LENGTH];
    int y[MAX_LENGTH];
    int length;
    char direction; // 'U', 'D', 'L', 'R'
};

void drawSnake(Snake snake) {
    for (int i = 0; i < snake.length; i++) {
        setcolor(GREEN);
        rectangle(snake.x[i], snake.y[i], snake.x[i] + 10, snake.y[i] + 10);
        floodfill(snake.x[i] + 5, snake.y[i] + 5, GREEN);
    }
}

void drawFood(int fx, int fy) {
    setcolor(RED);
    rectangle(fx, fy, fx + 10, fy + 10);
    floodfill(fx + 5, fy + 5, RED);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI"); // Ensure the correct path

    Snake snake;
    snake.length = 3; // Initial length
    snake.direction = 'R'; // Initial direction

    // Initial positions of the snake
    for (int i = 0; i < snake.length; i++) {
        snake.x[i] = 200 - i * 10; // Starting from the middle of the screen
        snake.y[i] = 200;
    }

    int foodX = rand() % (getmaxx() / 10) * 10;
    int foodY = rand() % (getmaxy() / 10) * 10;

    while (1) {
        if (kbhit()) {
            char key = getch();
            if (key == 27) break; // Escape key to exit

            // Change direction based on key press
            if (key == 'w' && snake.direction != 'D') snake.direction = 'U';
            else if (key == 's' && snake.direction != 'U') snake.direction = 'D';
            else if (key == 'a' && snake.direction != 'R') snake.direction = 'L';
            else if (key == 'd' && snake.direction != 'L') snake.direction = 'R';
        }

        // Move the snake
        for (int i = snake.length - 1; i > 0; i--) {
            snake.x[i] = snake.x[i - 1];
            snake.y[i] = snake.y[i - 1];
        }

        // Update the head of the snake based on direction
        if (snake.direction == 'U') snake.y[0] -= 10;
        else if (snake.direction == 'D') snake.y[0] += 10;
        else if (snake.direction == 'L') snake.x[0] -= 10;
        else if (snake.direction == 'R') snake.x[0] += 10;

        // Wrap around the screen
        if (snake.x[0] < 0) snake.x[0] = getmaxx() - 10; // Wrap left
        if (snake.x[0] >= getmaxx()) snake.x[0] = 0; // Wrap right
        if (snake.y[0] < 0) snake.y[0] = getmaxy() - 10; // Wrap up
        if (snake.y[0] >= getmaxy()) snake.y[0] = 0; // Wrap down

        // Check for collision with food
        if (snake.x[0] == foodX && snake.y[0] == foodY) {
            if (snake.length < MAX_LENGTH) snake.length++;
            foodX = rand() % (getmaxx() / 10) * 10;
            foodY = rand() % (getmaxy() / 10) * 10;
        }

        // Clear the screen
        cleardevice();

        // Draw snake and food
        drawSnake(snake);
        drawFood(foodX, foodY);

        // Delay for game speed
        delay(500);
    }

    closegraph();
    return 0;
}
