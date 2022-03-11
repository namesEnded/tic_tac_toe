#include "checks.h"


bool Checks::is3Equal(char a, char b, char c)
{
    return (a == b) && (b == c) && (a != '_');
}

bool Checks::is4Equal(char a, char b, char c, char d)
{
    return (a == b) && (b == c) && (c == d) && (a != '_');
}

char Checks::checkWinner(char** area, int areaSize)
{
        char winner = 'N';
        //Vertical win
        for(int i=0; i<3; i++ )
        {
            if (is3Equal(area[0][i], area[1][i], area[2][i]))
            {
                winner = area[0][i];
            }
        }

        //Horizontal win
        for(int i=0; i<3; i++ )
        {
            if (is3Equal(area[i][0], area[i][1], area[i][2]))
            {
              winner = area[i][0];
            }
        }

        //Diagonals win
        if (is3Equal(area[0][0], area[1][1], area[2][2]))
        {
            winner = area[0][0];
        }
        if (is3Equal(area[2][0], area[1][1], area[0][2]))
        {
            winner = area[2][0];
        }

        std::vector<Point> emptyCells = Checks::emptyCells(area, areaSize);
        int numberOfEmptyCells = emptyCells.size();
        if (numberOfEmptyCells == 0 && winner == 'N')
        {
            return 'T';
        }
        else
        {
            return winner;
        }
}

winState3x3 Checks::gameState3x3(char** area)
{
        char winner = 'N';
        winState3x3 win;
        win.winner = winner;

        //Vertical win
        for(int i=0; i<3; i++ )
        {
            if (is3Equal(area[0][i], area[1][i], area[2][i]))
            {
                win.winner = area[0][i];
                for(int k=0; k<3; k++ )
                {
                        win.points[k][0] = k;
                        win.points[k][1] = i;
                }
            }
        }

        //Horizontal win
        for(int i=0; i<3; i++ )
        {
            if (is3Equal(area[i][0], area[i][1], area[i][2]))
            {
              win.winner = area[i][0];
              for(int k=0; k<3; k++ )
              {
                  win.points[k][0] = i;
                  win.points[k][1] = k;
              }
            }
        }

        //Diagonals win
        if (is3Equal(area[0][0], area[1][1], area[2][2]))
        {
            win.winner = area[0][0];
            for(int k=0; k<3; k++ )
            {
                win.points[k][0] = k;
                win.points[k][1] = k;
            }
        }
        if (is3Equal(area[2][0], area[1][1], area[0][2]))
        {
            win.winner = area[2][0];
            int j = 3;
            for(int k=0; k<3; k++ )
            {
                j--;
                win.points[k][0] = j;
                win.points[k][1] = k;
            }
        }

        std::vector<Point> emptyCells = Checks::emptyCells(area, 3);
        int numberOfEmptyCells = emptyCells.size();
        if (numberOfEmptyCells == 0 && win.winner == 'N')
        {
            win.winner = 'T';
            for(int k=0; k<3; k++ )
            {
                win.points[k][0] = 0;
                win.points[k][1] = 0;
            }
            return win;
        }
        else
        {
            return win;
        }
}


std::vector<Point> Checks::emptyCells(char** area, int areaSize)
{
    std::vector<Point> empty;
    for(int i=0; i<areaSize; i++ )
    {
        for(int j=0; j<areaSize; j++ )
        {
            if (area[i][j]=='_')
            {
                Point p;
                p.i = i;
                p.j = j;
                empty.push_back(p);
            }
        }
    }
    return empty;
}

winState4x4 Checks::gameState4x4(char** area)
{
        char winner = 'N';
        winState4x4 win;
        win.winner = winner;

        //Vertical win
        for(int i=0; i<4; i++)
        {
            if (is4Equal(area[0][i], area[1][i], area[2][i], area[3][i]))
            {
                win.winner = area[0][i];
                for(int k=0; k<4; k++ )
                {
                        win.points[k][0] = k;
                        win.points[k][1] = i;
                }
            }
        }

        //Horizontal win
        for(int i=0; i<4; i++ )
        {
            if (is4Equal(area[i][0], area[i][1], area[i][2], area[i][3]))
            {
              win.winner = area[i][0];
              for(int k=0; k<4; k++ )
              {
                  win.points[k][0] = i;
                  win.points[k][1] = k;
              }
            }
        }

        //Diagonals win
        if (is4Equal(area[0][0], area[1][1], area[2][2], area[3][3]))
        {
            win.winner = area[0][0];
            for(int k=0; k<4; k++ )
            {
                win.points[k][0] = k;
                win.points[k][1] = k;
            }
        }
        if (is4Equal(area[3][0], area[2][1], area[1][2], area[0][3]))
        {
            win.winner = area[3][0];
            int j = 4;
            for(int k=0; k<4; k++ )
            {
                j--;
                win.points[k][0] = j;
                win.points[k][1] = k;
            }
        }

        std::vector<Point> emptyCells = Checks::emptyCells(area, 4);
        int numberOfEmptyCells = emptyCells.size();
        if (numberOfEmptyCells == 0 && win.winner == 'N')
        {
            win.winner = 'T';
            for(int k=0; k<4; k++ )
            {
                win.points[k][0] = 0;
                win.points[k][1] = 0;
            }
            return win;
        }
        else
        {
            return win;
        }
}


//std::vector<Point> Checks::emptyCells(char** area, int areaSize)
//{
//    std::vector<Point> empty;
//    for(int i=0; i<areaSize; i++ )
//    {
//        for(int j=0; j<areaSize; j++ )
//        {
//            if (area[i][j]=='_')
//            {
//                Point p;
//                p.i = i;
//                p.j = j;
//                empty.push_back(p);
//            }
//        }
//    }
//    return empty;
//}

//char players[2] = {currentUserShape,currentComputerShape};
int Checks::minimax3x3(char** area, int areaSize, int depth, bool isMaximize, char players[2])
{
    char result = gameState3x3(area).winner;
    //char result = checkWinner(area);
    if (result!='N')
    {
        if (result == players[1])
        {
            return 10 - depth;
        }
        else if (result == players[0])
        {
            return depth - 10;
        }
        else if (result == 'T')
        {
            return  0;
        }
    }


    if (isMaximize)
    {
        int best = -1000;
        for(int i=0; i<areaSize; i++ )
        {
            for(int j=0; j<areaSize; j++ )
            {
                if (area[i][j]=='_')
                {
                    area[i][j] =  players[1];
                    int minimaxScore = minimax3x3(area, areaSize, depth + 1 , false, players);
            //      Delete installed figure
                    area[i][j] = '_';
                    if (minimaxScore>best)
                    {
                        best = minimaxScore;
                    }
                    //best = std::max(minimaxScore, best);
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for(int i=0; i<areaSize; i++ )
        {
            for(int j=0; j<areaSize; j++ )
            {
                if (area[i][j]=='_')
                {
                    area[i][j] = players[0];
                    int minimaxScore = minimax3x3(area, areaSize, depth + 1 , true, players);
            //      Delete installed figure
                    area[i][j] = '_';
                    //best = std::min(minimaxScore, best);
                    if (minimaxScore<best)
                    {
                        best = minimaxScore;
                    }
                }
            }
        }
        return best;
    }
}

int Checks::minimax4x4(char** area, int areaSize, int depth, int alpha, int beta, bool isMaximize, char players[2])
{
    qDebug() << depth <<" - DEPTH";
    qDebug() << "||=====START-K-MEANS=====||";
    char result = gameState4x4(area).winner;
    //char result = checkWinner(area);
    if (result!='N')
    {
        if (result == players[1])
        {
            return 10 - depth;
        }
        else if (result == players[0])
        {
            return depth - 10;
        }
        else if (result == 'T')
        {
            return  0;
        }
    }


    if (isMaximize)
    {
        int best = -std::numeric_limits<int>::max();
        for(int i=0; i<areaSize; i++ )
        {
            for(int j=0; j<areaSize; j++ )
            {
                if (area[i][j]=='_')
                {
                    area[i][j] =  players[1];
                    int minimaxScore = minimax4x4(area, areaSize, depth - 1 , alpha, beta, false, players);
            //      Delete installed figure
                    area[i][j] = '_';
                    if (minimaxScore>best)
                    {
                        qDebug() << best <<" - PREV_BEST_MAX";
                        qDebug() << Qt::endl;
                        best = minimaxScore;
                        qDebug() << best <<" - NEW_BEST_MAX";
                        qDebug() << Qt::endl;

                        alpha = std::max(alpha, minimaxScore);
                        if (beta<=alpha)
                        {
                            break;
                        }
                    }
                    //best = std::max(minimaxScore, best);
                }
            }
        }
        return best;
    }
    else
    {
        int best = std::numeric_limits<int>::max();;
        for(int i=0; i<areaSize; i++ )
        {
            for(int j=0; j<areaSize; j++ )
            {
                if (area[i][j]=='_')
                {
                    area[i][j] = players[0];
                    int minimaxScore = minimax4x4(area, areaSize, depth - 1 , alpha, beta, true, players);
            //      Delete installed figure
                    area[i][j] = '_';
                    //best = std::min(minimaxScore, best);
                    if (minimaxScore<best)
                    {
                        qDebug() << best <<" - PREV_BEST_MIN";
                        qDebug() << Qt::endl;
                        best = minimaxScore;
                        qDebug() << best <<" - NEW_BEST_MIN";
                        qDebug() << Qt::endl;

                        beta = std::min(beta, minimaxScore);
                        if (beta<=alpha)
                        {
                            break;
                        }

                    }
                }
            }
        }
        return best;
    }
}


Point Checks::bestMove(char** area, int areaSize, char playerShape, char players[2])
{
    int best = -1000;

    Point move;
    move.j = -1;
    move.i = -1;

    for(int i=0; i<areaSize; i++ )
    {
        for(int j=0; j<areaSize; j++ )
        {
            if (area[i][j]=='_')
            {
                area[i][j] =  playerShape;
                int minimaxScore = areaSize == 4 ? minimax4x4(area, areaSize, 3 ,-std::numeric_limits<int>::max(),std::numeric_limits<int>::max(), false, players) : minimax3x3(area, areaSize, 0 , false, players);
                qDebug() << "||======END-ITER======||";
                qDebug() << Qt::endl;
                //int minimaxScore = minimax(area, areaSize, 0 , false, players);
        //      Delete installed figure
                area[i][j] = '_';
                if (minimaxScore>best)
                {
                    best = minimaxScore;
                    move.j = j;
                    move.i = i;
                }
            }
        }
    }
    return move;
}


std::pair<int, Point> Checks::bestMove4x4(char** area, int areaSize, char playerShape, char players[2], int depth, int alpha, int beta, bool isMaximize)
{
    Point move;
    move.j = -1;
    move.i = -1;
    int best = (playerShape == players[1]) ? -1000 : 1000;
    char result = gameState4x4(area).winner;
    if (result!='N' || depth == 2)
    {
        if (result == players[1])
        {
            return std::make_pair(1000, move);
        }
        else if (result == players[0])
        {
            return std::make_pair(-1000, move);
        }
        else if (result == 'T')
        {
            return  std::make_pair(0, move);
        }
    }
    for(int i=0; i<areaSize; i++ )
    {
        for(int j=0; j<areaSize; j++ )
        {
            if (area[i][j]=='_')
            {
                Point curMove;
                curMove.i = i;
                curMove.j = j;
                area[i][j] = playerShape;
                if (playerShape == players[1])
                {
                    int minimaxScore = bestMove4x4(area, areaSize, players[0], players, depth + 1, alpha, beta, false).first;
                    if (minimaxScore>best)
                    {
                        best = minimaxScore - depth * 10;
                        move = curMove;
                        alpha = std::max(alpha, best);
                        area[i][j] = '_';
                        if (beta<=alpha)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    int minimaxScore = bestMove4x4(area, areaSize, players[1], players, depth + 1, alpha, beta, true).first;
                    if (minimaxScore<best)
                    {
                        best = minimaxScore + depth * 10;
                        move = curMove;
                        alpha = std::min(beta, best);
                        area[i][j] = '_';
                        if (beta<=alpha)
                        {
                            break;
                        }
                    }
                }

                area[i][j] = '_';

            }
        }
    }








//    if (playerShape == players[0])
//    {
//        for(int i=0; i<areaSize; i++ )
//        {
//            for(int j=0; j<areaSize; j++ )
//            {
//                if (area[i][j]=='_')
//                {
//                    Point curMove;
//                    curMove.i = i;
//                    curMove.j = j;
//                    area[i][j] =  players[1];
//                    int minimaxScore = bestMove4x4(area, areaSize, players[1], players, depth + 1, alpha, beta, false).first;
//                    //area[i][j] = '_';
//                    //int minimaxScore = minimax4x4(area, areaSize, depth - 1 , alpha, beta, false, players);
//                    if (minimaxScore>best)
//                    {
//                        best = minimaxScore - depth * 10;
//                        move = curMove;
//                        alpha = std::max(alpha, best);
//                        area[i][j] = '_';
//                        if (beta<=alpha)
//                        {
//                            break;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    else
//    {
//        for(int i=0; i<areaSize; i++ )
//        {
//            for(int j=0; j<areaSize; j++ )
//            {
//                if (area[i][j]=='_')
//                {
//                    Point curMove;
//                    curMove.i = i;
//                    curMove.j = j;
//                    area[i][j] = players[0];
//                    int minimaxScore = bestMove4x4(area, areaSize, players[0], players, depth + 1, alpha, beta, true).first;
//                    //int minimaxScore = minimax4x4(area, areaSize, depth - 1 , alpha, beta, true, players);
//                    //best = std::min(minimaxScore, best);
//                    //area[i][j] = '_';
//                    if (minimaxScore<best)
//                    {
//                        best = minimaxScore + depth * 10;
//                        move = curMove;
//                        beta = std::min(beta, minimaxScore);
//                        area[i][j] = '_';
//                        if (beta<=alpha)
//                        {
//                            break;
//                        }

//                    }
//                }
//            }
//        }
//    }

    return std::make_pair(best, move);
}



void Checks::printCurAreaState(char** area, int areaSize)
{
    QString output = "";
    qDebug() << "||=====START-CHECKS=====||";
    for(int i=0; i<areaSize; i++ )
    {
        for(int j=0; j<areaSize; j++ )
        {
            output += QString(area[i][j]) + " ";
        }
        qDebug() << output << Qt::endl;
        output = "";
    }
    qDebug() << "||======END-CHECKS======||";
    qDebug() << Qt::endl;

}
