#ifndef CHECKS_H
#define CHECKS_H

#include <QDebug>
#include <vector>
#include <QString>
#include <map>

struct Point
{
    int i;
    int j;
};

struct winState3x3
{
    int points [3][2];
    char winner = 'N';
};

struct winState4x4
{
    int points [4][2];
    char winner = 'N';
};

class Checks
{
public:
    static bool is3Equal(char a, char b , char c);
    static bool is4Equal(char a, char b, char c, char d);
    static void printCurAreaState(char** area, int areaSize);
    static char checkWinner(char** area, int areaSize);
    static winState3x3 gameState3x3(char** area);
    static winState4x4 gameState4x4(char** area);
    static int gameState(char** area, int areaSize, int i, int j);
    static int gameState(char** area, int areaSize, int i, int j, char playerShape);
    static int gameState(char** area, int areaSize, char playerShape);
    static std::vector<Point> emptyCells(char** area, int areaSize);
    //static int minimax(char** area, int areaSize, int depth, bool isMax, char playerX, char playerO);
    //static int minimax(char** area, int areaSize, int depth, bool isMaximize,  char players[2]);
    static int minimax3x3(char** area, int areaSize, int depth, bool isMaximize, char players[2]);
    static int minimax4x4(char** area, int areaSize, int depth, int alpha, int beta, bool isMaximize, char players[2]);
    static void move(char** area, int areaSize, char player);
    static Point bestMove(char** area, int areaSize, char player, char playerX, char playerO);
    static Point bestMove(char** area, int areaSize, char player, char players[2]);
    static std::pair<int, Point> bestMove4x4(char** area, int areaSize, char playerShape, char players[2], int depth, int alpha, int beta, bool isMaximize);
};


#endif // CHECKS_H
