#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newgameform.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int s = 0; s < 9; ++s) {
        ui->board->setRowHeight(s,ui->board->height()/9);
    }
    for (int s = 0; s < 9; ++s) {
        ui->board->setColumnWidth(s,ui->board->width()/9);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete newgameform;
}



void MainWindow::getData(){
    newgameform = new NewGameForm(this);
    newgameform->show();
    this->players_count = newgameform->getPlayersCount();
    this->player1 = newgameform->getPlayer1Name();
    this->player2 = newgameform->getPlayer2Name();
    this->game_mode = newgameform->getGameMode();
    //delete newgameform;
}

void MainWindow::on_newGame_clicked()
{
    getData();
    if(game_mode == "SUS"){
        ui->board->setColumnCount(3);
        ui->board->setRowCount(3);
    } else {
        ui->board->setColumnCount(9);
        ui->board->setRowCount(9);
    }
}

