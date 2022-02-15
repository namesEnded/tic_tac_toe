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
    if (isLocked)
    {
        QString style = (currentComputerShape=='X') ? StyleHelper::getXFieldStyle() : StyleHelper::getOFieldStyle();
        char players[2] = {currentUserShape,currentComputerShape};
        Point movePoint = Checks::bestMove(area, currentComputerShape,players);
        area[movePoint.i][movePoint.j] = currentComputerShape;
        changeSpecialButtonStyle(movePoint.i, movePoint.j, style);
        printCurAreaState();

        //int resO = Checks::gameState(area, currentComputerShape);
        //int resX = Checks::gameState(area, currentUserShape);
        std::vector<Point> vectorOfEmptyCells = Checks::emptyCells(area);
        int numberOfEmptyCells = vectorOfEmptyCells.size();

        qDebug() << "POINT: " + QString::number(movePoint.i) + ";"+QString::number(movePoint.j) << Qt::endl;
        //qDebug() << "O STATUS: " + QString::number(resO) << Qt::endl;
        //qDebug() << "X STATUS: " + QString::number(resX) << Qt::endl;
        qDebug() << "NUM OF EMPTY CELLS: " + QString::number(numberOfEmptyCells) << Qt::endl;
        if(!isEnd())
        {
            isLocked = false;
        }
    }
}

void MainWindow::resetArea()
{
    for (auto& outer : area)
    {
        for (auto& inner : outer)
        {
            inner = '_';
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
       x->setStyleSheet(StyleHelper::getTieButtonStyle());
    }
}

void MainWindow::configAreaButtons()
{
    QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tabWidget->widget(0)->layout());
    for(int i=0; i<3; i++)
    {
       for(int j=0; j<3; j++)
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
    QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tabWidget->widget(0)->layout());
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
        QPushButton *button = qobject_cast<QPushButton*>(sender());
        int row = button->property("row").toInt();
        int column = button->property("column").toInt();
        if (area[row][column]=='_')
        {
            area[row][column] = currentUserShape;
            QString style = (currentUserShape=='X') ? StyleHelper::getXFieldStyle() : StyleHelper::getOFieldStyle();
            button->setStyleSheet(style);
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
    }
}

bool MainWindow::isEnd()
{
    QString style;
    bool stop = true;
    winState res = Checks::gameState(area);
    if (res.winner!='N')
    {
        if (res.winner == currentUserShape)
        {
            style = (res.winner == 'X')? StyleHelper::getXWinFieldStyle() : StyleHelper::getOWinFieldStyle();
        }
        else if (res.winner == currentComputerShape)
        {
            style = (res.winner == 'X')? StyleHelper::getXLoseFieldStyle() : StyleHelper::getOLoseFieldStyle();
        }
        if (res.winner == 'T')
        {
            setTieButtonStyle();
        }
        else
        {
            for(int i = 0; i<3; i++)
            {
                changeSpecialButtonStyle(res.points[i][0], res.points[i][1], style);
            }
        }
        delayUI(1);
        isLocked = true;
        ui->startBtn->setDisabled(true);
        inProgress = false;
        resetButtonsStyle();
        ui->startBtn->setDisabled(false);
        ui->startBtn->setText("Start");
        ui->XButton->setDisabled(false);
        ui->OButton->setDisabled(false);
    }
    else
    {
        stop = false;
    }
    return stop;
}

void MainWindow::checkWhoIsFirst()
{
    isLocked = (currentUserShape=='X') ? false : true;
}

void MainWindow::printCurAreaState()
{
    QString output = "";
    qDebug() << "||=====START=====||";
    for(int i=0; i<3; i++ )
    {
        for(int j=0; j<3; j++ )
        {
            output += QString(area[i][j]) + " ";
        }
        qDebug() << output << Qt::endl;
        output = "";
    }
    qDebug() << "||======END======||";
    qDebug() << Qt::endl;
}

