#include "maze.h"

struct XY {
    int x;
    int y;
    bool operator==(const XY& other) const { return x == other.x && y == other.y; }
    bool operator!=(const XY& other) const { return x != other.x || y != other.y; }
};

const int map_size = 32;

bool isWall(const unsigned int* maze, int x, int y) {
    return (maze[y] >> (map_size - 1 - x)) & 1;
}

bool canMove(unsigned int* maze, int x, int y) {
    return x >= 0 && x < map_size && y >= 0 && y < map_size && !isWall(maze, x, y);
}

void draw_wall() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 255); printf("++"); }
void draw_entry_exit() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 34); printf("__"); }
void draw_solution() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 51); printf("__"); }
void draw_path() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0); printf("__"); }
void draw_player() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 110); printf("<>"); }

void choise_object(unsigned int* maze, XY coord, XY start, XY end) {
    if (isWall(maze, coord.x, coord.y)) draw_wall();
    else if (coord == start) draw_entry_exit();
    else if (coord == end) draw_entry_exit();
    else draw_path();
}

void movePlayer(unsigned int* maze, XY& player, int dx, int dy, int x, int y, XY start, XY end) {
    int nx = player.x + dx;
    int ny = player.y + dy;

    if (!canMove(maze, nx, ny)) {
        Beep(750, 150);
        return;
    }

    SetMazeCursorPosition(x + player.x * 2, y + player.y);
    choise_object(maze, player, start, end);

    player.x = nx;
    player.y = ny;

    SetMazeCursorPosition(x + player.x * 2, y + player.y);
    draw_player();
}

void find_exit(unsigned int* maze, int x, int y, XY player, XY finish) {
    bool visited[map_size][map_size] = {};
    XY parent[map_size][map_size];

    XY queue[map_size * map_size];
    int start = 0, end = 0;

    queue[end++] = player;
    visited[player.y][player.x] = true;

    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };

    while (start < end) {
        XY cur = queue[start++];

        if (cur == finish)
            break;

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (canMove(maze, nx, ny) && !visited[ny][nx]) {
                visited[ny][nx] = true;
                parent[ny][nx] = cur;
                queue[end++] = { nx, ny };
            }
        }
    }

    if (!visited[finish.y][finish.x])
        return;

    XY cur = finish;
    while (cur != player) {
        if (cur != finish) {
            SetMazeCursorPosition(x + cur.x * 2, y + cur.y);
            draw_solution();
        }
        cur = parent[cur.y][cur.x];
    }
}
void draw_maze(int X, int Y, unsigned int* maze, XY start, XY end) {
    SetMazeCursorPosition(X, Y);

    for (int y = 0; y < map_size; y++) {
        for (int x = 0; x < map_size; x++) {
            choise_object(maze, { x, y }, start, end);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printf("|\n");
    }
}

int Lab_Maze() {
    system("cls");
    Info2();
    printf("Лабиринт.\nУправление - стрелками. ESC - выход. F5 - показать путь.\n\n");

    unsigned int map[32] = {
        0b11111111111111111111111111111101,
        0b10000000000000000000000000000001,
        0b10101110111010111011111011101111,
        0b10100010001010001000001000100001,
        0b10111011101110111011101110111101,
        0b10001000100010001000100010001101,
        0b10101011111010111110101111101101,
        0b10101000001010000010100000101101,
        0b10111110101111101011111010111111,
        0b10000010100000101000001010000001,
        0b10101110111011101110111011101111,
        0b10100010001000100010001000100001,
        0b10111010111110101111101011111101,
        0b10001010000010100000101000001101,
        0b11101111101011111010111110101111,
        0b11100000101000001010000010100001,
        0b11111010101110111011101110111101,
        0b10001010100010001000100010001101,
        0b10101010111111111010101011111111,
        0b10101010000000001010101000000001,
        0b10111011101010111111101010111111,
        0b10000000101010000000101010000001,
        0b10101110111011101110111011101111,
        0b10100010001000100010001000100001,
        0b10111011101110111011101110111101,
        0b10001000100010001000100010001101,
        0b10101011111010111110101111101101,
        0b10101000001010000010100000101101,
        0b10101110101011101010111010111111,
        0b10111110101111101011111010000001,
        0b10000010100000111000001011111101,
        0b11111111111111111111111111111101
    };

    XY start{ 30, 0 };
    XY end{ 30, 31 };
    XY player = start;

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    CONSOLE_SCREEN_BUFFER_INFO coord;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coord);
    int X = coord.dwCursorPosition.X;
    int Y = coord.dwCursorPosition.Y;

    draw_maze(X, Y, map, start, end);
    SetMazeCursorPosition(X + player.x * 2, Y + player.y);
    draw_player();

    unsigned char ch = 0;
    do {
        ch = _getch();

        switch (ch) {
        case 224:
            switch (_getch()) {
            case 80: movePlayer(map, player, 0, 1, X, Y, start, end); break;
            case 75: movePlayer(map, player, -1, 0, X, Y, start, end); break;
            case 77: movePlayer(map, player, 1, 0, X, Y, start, end); break;
            case 72: movePlayer(map, player, 0, -1, X, Y, start, end); break;
            }
            break;

        case 0:
            switch (_getch()) {
            case 63:
                draw_maze(X, Y, map, start, end);
                SetMazeCursorPosition(X + player.x * 2, Y + player.y);
                draw_player();
                find_exit(map, X, Y, player, end);
                break;
            }
            break;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        if (player == end) {
            victory();
            break;
        }

    } while (ch != 27);

    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    if (ch == 27) {
        system("cls");
        Info2();
        printf("Аварийный выход.\n\n");
    }

    system("pause");
    return 0;
}