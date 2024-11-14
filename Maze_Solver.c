#include <stdio.h>

#define ROWS 5
#define COLS 5

// Stack structure
typedef struct {
    int x, y;
} Point;

Point stack[100];
int top = -1;

// Maze with 0 as path and 1 as wall
int maze[ROWS][COLS];

// Movement directions: right, down, left, up
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

// Push a point onto the stack
void push(int x, int y) {
    stack[++top].x = x;
    stack[top].y = y;
}

// Pop a point from the stack
Point pop() {
    return stack[top--];
}

// Check if position is valid
int isValid(int x, int y, int visited[ROWS][COLS]) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] == 0 && !visited[x][y];
}

// Print the maze
void printMaze() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == -1) {
                printf("* "); // Print '*' for the path
            }
            else {
                printf("%d ", maze[i][j]);
            }
        }
        printf("\n");
    }
}

// Solve the maze using a stack
int solveMaze(int startX, int startY, int endX, int endY) {
    int visited[ROWS][COLS] = {0};  // Keep track of visited points
    push(startX, startY);
    visited[startX][startY] = 1;
    maze[startX][startY] = -1; // Mark start position

    while (top != -1) {
        Point p = pop();

        // If we reach the end point
        if (p.x == endX && p.y == endY) {
            printf("Path found!\n");
            return 1;
        }

        // Try all four directions
        for (int i = 0; i < 4; i++) {
            int newX = p.x + dx[i];
            int newY = p.y + dy[i];

            if (isValid(newX, newY, visited)) {
                push(newX, newY);
                visited[newX][newY] = 1;
                maze[newX][newY] = -1; // Mark the path
            }
        }
    }

    printf("No path found.\n");
    return 0;
}

int main() {
    printf("Form the MAZE (5x5)\n");
    printf("Enter 0 for path and 1 for wall:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    int startX = 0, startY = 0; // Starting point
    int endX = 4, endY = 4;     // Ending point

    if (solveMaze(startX, startY, endX, endY)) {
        printMaze(); // Print the maze showing the path taken
    } 
    else {
        printMaze(); // Print the maze even if no path was found
    }

    return 0;
}
