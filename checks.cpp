#include "checks.h"


bool Checks::is3Equal(char a, char b, char c)
{
    return (a == b) && (b == c) && (a != '_');
}

char Checks::checkWinner(char area[3][3])
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

//    int numOfEmpty = 0;
//    for(int i=0; i<3; i++ )
//    {
//        for(int j=0; j<3; j++ )
//        {
//            if (area[i][j]=='_')
//            {
//                numOfEmpty++;
//            }
//        }
//    }

    std::vector<Point> emptyCells = Checks::emptyCells(area);
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

winState Checks::gameState(char area[3][3])
{
        char winner = 'N';
        winState win;
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

        std::vector<Point> emptyCells = Checks::emptyCells(area);
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


std::vector<Point> Checks::emptyCells(char area[3][3])
{
    std::vector<Point> empty;
    for(int i=0; i<3; i++ )
    {
        for(int j=0; j<3; j++ )
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


//char players[2] = {currentUserShape,currentComputerShape};
int Checks::minimax(char area[3][3], int depth, bool isMaximize, char players[2])
{
    char result = gameState(area).winner;
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
        for(int i=0; i<3; i++ )
        {
            for(int j=0; j<3; j++ )
            {
                if (area[i][j]=='_')
                {
                    area[i][j] =  players[1];
                    int minimaxScore = minimax(area, depth + 1 , false, players);
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
        for(int i=0; i<3; i++ )
        {
            for(int j=0; j<3; j++ )
            {
                if (area[i][j]=='_')
                {
                    area[i][j] = players[0];
                    int minimaxScore = minimax(area, depth + 1 , true, players);
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

Point Checks::bestMove(char area[3][3], char playerShape, char players[2])
{
    int best = -1000;

    Point move;
    move.j = -1;
    move.i = -1;

    for(int i=0; i<3; i++ )
    {
        for(int j=0; j<3; j++ )
        {
            if (area[i][j]=='_')
            {
                area[i][j] =  playerShape;
                int minimaxScore = minimax(area, 0 , false, players);
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

void Checks::printCurAreaState(char area[3][3])
{
    QString output = "";
    qDebug() << "||=====START-CHECKS=====||";
    for(int i=0; i<3; i++ )
    {
        for(int j=0; j<3; j++ )
        {
            output += QString(area[i][j]) + " ";
        }
        qDebug() << output << Qt::endl;
        output = "";
    }
    qDebug() << "||======END-CHECKS======||";
    qDebug() << Qt::endl;
}
