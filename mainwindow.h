#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newgameform.h"

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

private:
    Ui::MainWindow *ui;
    NewGameForm *newgameform;
    int players_count;
    QString game_mode;
    QString player1;
    QString player2;

};
#endif // MAINWINDOW_H
