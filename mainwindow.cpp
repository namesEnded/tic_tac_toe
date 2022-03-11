#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabBar>
#include "stylehelper.h"
#include <QStyleOption>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QFontDatabase>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <QTime>
#include <string>
#include <QTextStream>
#include "checks.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();
    setAreaSize();
    setInterfaceStyle();
    configAreaButtons();

    int fontID = QFontDatabase::addApplicationFont(":/res/fonts/MyriadPro-Light.otf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontID).at(0);
    qDebug() << fontFamily;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this );
    QWidget::paintEvent(event);
}


void MainWindow::setInterfaceStyle()
{

    resetButtonsStyle();
    setStartButtonStyle();
    ui->XButton->setStyleSheet(StyleHelper::getXStyle());
    ui->OButton->setStyleSheet(StyleHelper::getOActiveStyle());
//    changeSpecialButtonStyle(0, 0, StyleHelper::getXWinFieldStyle());
    this->setStyleSheet(StyleHelper::getMainWidgetStyle());
}

void MainWindow::game()
{
    if (inProgress)
    {
        isLocked = true;
        setGiveUpButtonStyle();
        ui->startBtn->setDisabled(true);
        delayUI(1);
        inProgress = false;
        resetButtonsStyle();
        ui->startBtn->setDisabled(false);
        ui->startBtn->setText("Start");
        ui->XButton->setDisabled(false);
        ui->OButton->setDisabled(false);
    }
    else
    {
        inProgress = true;
        checkWhoIsFirst();
        ui->startBtn->setText("Give up");
        resetArea();
        resetButtonsStyle();
        ui->XButton->setDisabled(true);
        ui->OButton->setDisabled(true);
        if (isLocked)
        {
            computerTurn();
        }
    }

}

void MainWindow::resetButtonsStyle()
{
    QList<QPushButton*> list = ui->tabWidget->findChildren<QPushButton*>();
    foreach(QPushButton *x, list) {
       QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
       effect->setBlurRadius(10);
       effect->setXOffset(1);
       effect->setYOffset(2);
       effect->setColor(QColor("#d2d2d2"));
       x->setGraphicsEffect(effect);
       x->setStyleSheet(StyleHelper::getBlankButtonStyle());
       //qDebug() << x->text() << x->objectName();
    }
}

void MainWindow::computerTurn()
{
    char**area = new char* [areaSize];
    for (int i = 0; i < areaSize; i++)
    {
    area[i] = new char [areaSize];
    }
    selectedArrayToSpecial(area);


    std::vector<Point> vectorOfEmptyCells = Checks::emptyCells(area, areaSize);
    int numberOfEmptyCells = vectorOfEmptyCells.size();

    if (numberOfEmptyCells==0) isEnd();
    if (isLocked)
    {
        QString style = (currentComputerShape=='X') ? StyleHelper::getXFieldStyle() : StyleHelper::getOFieldStyle();
        char players[2] = {currentUserShape,currentComputerShape};
        Point movePoint;
        movePoint.i = 0;
        movePoint.j = 0;
        if (areaSize == 4)
        {
            std::pair<int, Point> computerMove =Checks::bestMove4x4(area, areaSize, currentComputerShape,players, 0, -1000, 1000, false);
            movePoint.i = computerMove.second.i;
            movePoint.j = computerMove.second.j;
        }
        else if (areaSize == 3)
        {
            std::pair<int, Point> computerMove =Checks::bestMove4x4(area, areaSize, currentComputerShape,players, 0, -1000, 1000, false);
            movePoint.i = computerMove.second.i;
            movePoint.j = computerMove.second.j;
            //movePoint = Checks::bestMove(area, areaSize, currentComputerShape,players);
        }
        area[movePoint.i][movePoint.j] = currentComputerShape;
        changeSpecialButtonStyle(movePoint.i, movePoint.j, style);
        specialToSelectedArray(area);
        printCurAreaState();

        qDebug() << "POINT: " + QString::number(movePoint.i) + ";"+QString::number(movePoint.j) << Qt::endl;
        //qDebug() << "O STATUS: " + QString::number(resO) << Qt::endl;
        //qDebug() << "X STATUS: " + QString::number(resX) << Qt::endl;
        qDebug() << "NUM OF EMPTY CELLS: " + QString::number(numberOfEmptyCells) << Qt::endl;
        if(!isEnd())
        {
            isLocked = false;
        }
    }



    for (int i =0; i < areaSize; i++)
    {
        delete[] area[i];
    }

    delete[] area;
}

void MainWindow::resetArea()
{

    if (areaSize == 3)
    {
        for (auto& outer : area_3x3)
        {
            for (auto& inner : outer)
            {
                inner = '_';
            }
        }
    }
    else if (areaSize == 4)
    {
        for (auto& outer : area_4x4)
        {
            for (auto& inner : outer)
            {
                inner = '_';
            }
        }
    }
}

void MainWindow::changeButtonStyle(int num)
{
    if (num == 1)
    {
        ui->XButton->setStyleSheet(StyleHelper::getXActiveStyle());
        ui->OButton->setStyleSheet(StyleHelper::getOStyle());
    }
    else
    {
        ui->XButton->setStyleSheet(StyleHelper::getXStyle());
        ui->OButton->setStyleSheet(StyleHelper::getOActiveStyle());
    }
}

void MainWindow::delayUI(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::setStartButtonStyle()
{
    QGraphicsDropShadowEffect *startBtnShadowEffect = new QGraphicsDropShadowEffect;
    startBtnShadowEffect->setBlurRadius(10);
    startBtnShadowEffect->setXOffset(1);
    startBtnShadowEffect->setYOffset(2);
    startBtnShadowEffect->setColor(QColor("#d2d2d2"));
    ui->startBtn->setGraphicsEffect(startBtnShadowEffect);
}

void MainWindow::setGiveUpButtonStyle()
{
    QList<QPushButton*> list = ui->tabWidget->findChildren<QPushButton*>();
    foreach(QPushButton *x, list) {
       x->setStyleSheet(StyleHelper::getGiveUpButtonStyle());
    }
}

void MainWindow::setTieButtonStyle()
{
    QList<QPushButton*> list = ui->tabWidget->findChildren<QPushButton*>();
    foreach(QPushButton *x, list) {
       QString oldStyle = x->styleSheet();
       QString style = oldStyle +StyleHelper::getTieButtonStyle();
       x->setStyleSheet(StyleHelper::getTieButtonStyle());
//     x->setStyleSheet(style);
    }
}

void MainWindow::configAreaButtons()
{
//    if (ui->tabWidget->currentIndex() == 0)
//    {
//        QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tabWidget->widget(0)->layout());
//        for(int i=0; i<3; i++)
//        {
//           for(int j=0; j<3; j++)
//           {
//               QPushButton *button = qobject_cast<QPushButton*>(grid->itemAtPosition(i, j)->widget());
//               button->setProperty("row", i);
//               button->setProperty("column", j);
//               connect(button, &QPushButton::clicked, this, &MainWindow::onAreaButtonClicked);
//           }
//        }
//    }
//    else if (ui->tabWidget->currentIndex() == 1)
//    {
//        QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tabWidget->widget(1)->layout());
//        for(int i=0; i<4; i++)
//        {
//           for(int j=0; j<4; j++)
//           {
//               QPushButton *button = qobject_cast<QPushButton*>(grid->itemAtPosition(i, j)->widget());
//               button->setProperty("row", i);
//               button->setProperty("column", j);
//               connect(button, &QPushButton::clicked, this, &MainWindow::onAreaButtonClicked);
//           }
//        }
//    }


    QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tabWidget->widget(ui->tabWidget->currentIndex())->layout());
    for(int i=0; i<areaSize; i++)
    {
       for(int j=0; j<areaSize; j++)
       {
           QPushButton *button = qobject_cast<QPushButton*>(grid->itemAtPosition(i, j)->widget());
           button->setProperty("row", i);
           button->setProperty("column", j);
           connect(button, &QPushButton::clicked, this, &MainWindow::onAreaButtonClicked);
       }
    }

}

void MainWindow::changeSpecialButtonStyle(int i, int j, QString buttonStyle)
{
    QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tabWidget->widget(ui->tabWidget->currentIndex())->layout());
    //QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tabWidget->widget(0)->layout());
    QPushButton *button = qobject_cast<QPushButton*>(grid->itemAtPosition(i, j)->widget());
    button->setStyleSheet(buttonStyle);
}

void MainWindow::on_XButton_clicked()
{
    changeButtonStyle(1);
    currentUserShape = 'X';
    currentComputerShape = 'O';
}


void MainWindow::on_OButton_clicked()
{
    changeButtonStyle(2);
    currentUserShape = 'O';
    currentComputerShape = 'X';
}


void MainWindow::on_startBtn_clicked()
{
    if (ui->startBtn->text()=="Give up")
    {
       compRow = 1;
       compColumn = 0;
       isPlayerGiveUp = true;
       game();
    }
    else
    {
       game();
    }
}

void MainWindow::onAreaButtonClicked()
{
    if (!isLocked)
    {
        char**area = new char* [areaSize];
        for (int i = 0; i < areaSize; i++)
        {
        area[i] = new char [areaSize];
        }

        selectedArrayToSpecial(area);

        QPushButton *button = qobject_cast<QPushButton*>(sender());
        int row = button->property("row").toInt();
        int column = button->property("column").toInt();
        if (area[row][column]=='_')
        {
            area[row][column] = currentUserShape;
            QString style = (currentUserShape=='X') ? StyleHelper::getXFieldStyle() : StyleHelper::getOFieldStyle();
            button->setStyleSheet(style);
            specialToSelectedArray(area);
            printCurAreaState();
            if (!isEnd())
            {
                isLocked = true;
                computerTurn();
            }
        }
        else
        {
            QString style = (area[row][column]=='X') ? StyleHelper::getXLoseFieldStyle() : StyleHelper::getOLoseFieldStyle();
            button->setStyleSheet(style);
            delayUI(1);
            style = (area[row][column]=='X') ? StyleHelper::getXFieldStyle() : StyleHelper::getOFieldStyle();
            button->setStyleSheet(style);
        }

        for (int i =0; i < areaSize; i++)
        {
            delete[] area[i];
        }
        delete[] area;
    }
}

void MainWindow::setAreaSize()
{
    areaSize = 3;

    if (ui->tabWidget->currentIndex() == 1)
    {
       areaSize = 4;
    }

}

void MainWindow::selectedArrayToSpecial(char **area)
{
    if (areaSize == 4)
    {
        for (int i =0; i < areaSize; i++)
        {
            for (int j =0; j < areaSize; j++)
            {
                area[i][j] = area_4x4[i][j];
            }
        }
    }
    else if(areaSize == 3)
    {
        for (int i =0; i < areaSize; i++)
        {
            for (int j =0; j < areaSize; j++)
            {
                area[i][j] = area_3x3[i][j];
            }
        }
    }
}

void MainWindow::specialToSelectedArray(char **area)
{
    if (areaSize == 4)
    {
        for (int i =0; i < areaSize; i++)
        {
            for (int j =0; j < areaSize; j++)
            {
                area_4x4[i][j] = area[i][j];
            }
        }
    }
    else if(areaSize == 3)
    {
        for (int i =0; i < areaSize; i++)
        {
            for (int j =0; j < areaSize; j++)
            {
                area_3x3[i][j] = area[i][j] ;
            }
        }
    }
}

bool MainWindow::isEnd()
{
    char**area = new char* [areaSize];
    for (int i = 0; i < areaSize; i++)
    {
        area[i] = new char [areaSize];
    }
    int points3x3 [3][2] = {{0, 0},
                            {0, 0},
                            {0, 0}};

    int points4x4 [4][2] = {{0, 0},
                            {0, 0},
                            {0, 0},
                            {0, 0}};

    selectedArrayToSpecial(area);
    QString style;
    bool stop = true;
    char winner;
    if (areaSize == 3)
    {
        winState3x3 res = Checks::gameState3x3(area);
        winner = res.winner;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; i < 2; i++)
            {
                points3x3[i][j] = res.points[i][j];
            }
        }
    }
    else {
        winState4x4 res = Checks::gameState4x4(area);
        winner = res.winner;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; i < 2; i++)
            {
                points4x4[i][j] = res.points[i][j];
            }
        }
    }

    if (winner!='N')
    {
        if (winner == currentUserShape)
        {
            style = (winner == 'X')? StyleHelper::getXWinFieldStyle() : StyleHelper::getOWinFieldStyle();
        }
        else if (winner == currentComputerShape)
        {
            style = (winner == 'X')? StyleHelper::getXWinFieldStyle() : StyleHelper::getOWinFieldStyle();
        }
        if (winner == 'T')
        {
            setTieButtonStyleArea(area);
        }
        else
        {
            if (areaSize == 3)
            {
                for(int i = 0; i<3; i++)
                {
                    changeSpecialButtonStyle(points3x3[i][0], points3x3[i][1], style);
                }
            }
            else if (areaSize == 4)
            {
                for(int i = 0; i<4; i++)
                {
                    changeSpecialButtonStyle(points4x4[i][0], points4x4[i][1], style);
                }
            }
        }
        ui->startBtn->setDisabled(true);
        ui->startBtn->setDisabled(false);
        ui->startBtn->setText("Start");
        ui->XButton->setDisabled(false);
        ui->OButton->setDisabled(false);
        inProgress = false;
        isLocked = true;
        delayUI(1);
        resetButtonsStyle();
    }
    else
    {
        stop = false;
    }
    return stop;
}

void MainWindow::setTieButtonStyleArea(char **area)
{
    for(int i=0; i<areaSize; i++ )
    {
        for(int j=0; j<areaSize; j++ )
        {
            QString style = (area[i][j]=='X') ? StyleHelper::getXTieFieldStyle() : StyleHelper::getOTieFieldStyle();
            changeSpecialButtonStyle(i , j, style);
        }
    }
}


void MainWindow::checkWhoIsFirst()
{
    isLocked = (currentUserShape=='X') ? false : true;
}

void MainWindow::printCurAreaState()
{
    char**area = new char* [areaSize];
    for (int i = 0; i < areaSize; i++)
    {
    area[i] = new char [areaSize];
    }

    selectedArrayToSpecial(area);


    QString output = "";
    qDebug() << "||=====START=====||";
    for(int i=0; i<areaSize; i++ )
    {
        for(int j=0; j<areaSize; j++ )
        {
            output += QString(area[i][j]) + " ";
        }
        qDebug() << output << Qt::endl;
        output = "";
    }
    qDebug() << "||======END======||";
    qDebug() << Qt::endl;

    for (int i =0; i < areaSize; i++)
    {
        delete[] area[i];
    }

    delete[] area;
}

