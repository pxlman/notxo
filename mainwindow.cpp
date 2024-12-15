#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newgameform.h"
#include <QMessageBox>
#include <QWidgetItem>
#include "modules/SusGame.h"
#include "modules/BigTicTacToe.h"
#include "modules/BoardGame_Classes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::refreshBoard(int size){
    ui->board->setColumnCount(size);
    ui->board->setRowCount(size);
    for (int s = 0; s < size; ++s) {
        ui->board->setRowHeight(s,ui->board->height()/size);
    }
    for (int s = 0; s < size; ++s) {
        ui->board->setColumnWidth(s,ui->board->width()/size);
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
    this->player1_name = newgameform->getPlayer1Name();
    this->player2_name = newgameform->getPlayer2Name();
    this->game_mode = newgameform->getGameMode();
    if(game_mode == "SUS"){
        refreshBoard(3);
        players[0] = new Sus_Player(player1_name.toStdString(),'S');
        board = new Sus_Board();
        if(players_count >= 2)
            players[1] = new Sus_Player(player2_name.toStdString(), 'U');
        else
            players[1] = new Sus_RandomPlayer(player2_name.toStdString(), 'U');
    } else {
        refreshBoard(9);
        players[0] = new Big_Player(player1_name.toStdString(),'S');
        board = new BigBoard();
        if(players_count >= 2)
            players[1] = new Big_Player(player2_name.toStdString(), 'U');
        else
            players[1] = new Big_RandomPlayer(player2_name.toStdString(), 'U');
    }
    //delete newgameform;
}

void MainWindow::on_newGame_clicked()
{
    getData();
    if(game_mode == "SUS"){
        refreshBoard(3);
    } else {
        refreshBoard(9);
    }
}


void MainWindow::on_board_cellClicked(int row, int column)
{
    if(!board->game_is_over()){
        board->update_board(column, row, players[turn]->getsymbol());
        if(board->game_is_over()){
            if(board->is_win()){
                ui->winner_label->setText("<html><head/><body><p><span style=' color:#2ec27e;'>"+ QString::fromStdString(players[turn]->getname()) +" WINS</span></p></body></html>");
            } else {
                ui->winner_label->setText("<html><head/><body><p><span style=' color:#444444;'> Draw</span></p></body></html>");
            }
        } else {
            turn != turn;
        }
    }
}

