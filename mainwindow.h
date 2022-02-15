#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    char getCurrentUserShape();
    char getCurrentComputerShape();

protected:
        void paintEvent(QPaintEvent *event);
private slots:
        void on_XButton_clicked();

        void on_OButton_clicked();

        void on_startBtn_clicked();

        void onAreaButtonClicked();

private:
    char currentUserShape = 'X';
    char currentComputerShape = 'O';
    Ui::MainWindow *ui;
    char area[3][3] = {
      {'_','_','_'},
      {'_','_','_'},
      {'_','_','_'}
    };
    int compRow = 0;
    int compColumn = 2;
    bool inProgress = false;
    bool isLocked = true;
    bool isPlayerWin = false;
    bool isPlayerGiveUp= false;
    bool isEnd();
    void checkWhoIsFirst();
    void printCurAreaState();
    void setInterfaceStyle();
    void game();
    void resetButtonsStyle();
    void computerTurn();
    void resetArea();
    void changeButtonStyle(int num);
    void delayUI(int n);
    void setTieButtonStyle();
    void setStartButtonStyle();
    void setGiveUpButtonStyle();
    void configAreaButtons();
    void changeSpecialButtonStyle(int i, int j, QString buttonStyle);
};
#endif // MAINWINDOW_H
