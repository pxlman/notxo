#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newgameform.h"
#include "modules/BoardGame_Classes.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void getData();
    ~MainWindow();

private slots:
    void on_newGame_clicked();

    void on_board_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    NewGameForm *newgameform;
    int players_count;
    QString game_mode;
    QString player1_name;
    QString player2_name;
    Player<char>* players[2];
    Board<char>* board;
    bool turn = 0;
    void refreshBoard(int size = 3);
};
#endif // MAINWINDOW_H
