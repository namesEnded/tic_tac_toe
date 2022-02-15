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

struct winState
{
    int points [3][2];
    char winner = 'N';
};

class Checks
{
public:
    static bool is3Equal(char a, char b , char c);
    static void printCurAreaState(char area[3][3]);
    static char checkWinner(char area[3][3]);
    static winState gameState(char area[3][3]);
    static int gameState(char area[3][3], int i, int j);
    static int gameState(char area[3][3], int i, int j, char playerShape);
    static int gameState(char area[3][3], char playerShape);
    static std::vector<Point> emptyCells(char area[3][3]);
    static int minimax(char area[3][3], int depth, bool isMax, char playerX, char playerO);
    static int minimax(char area[3][3], int depth, bool isMaximize,  char players[2]);
    static void move(char area[3][3], char player);
    static Point bestMove(char area[3][3], char player, char playerX, char playerO);
    static Point bestMove(char area[3][3], char player, char players[2]);
};


#endif // CHECKS_H
