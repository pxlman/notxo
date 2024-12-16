#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newgameform.h"
#include <QMessageBox>
#include <QWidgetItem>
#include "modules/SusGame.h"
#include "modules/BigTicTacToe.h"
#include "modules/BoardGame_Classes.h"
#include <QDebug>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    newgameform = new NewGameForm(this);
    ui->setupUi(this);
    // hide the play again button
    ui->playagain->setHidden(true);
}

// Refresh the board to a suitable clear one
void MainWindow::refreshBoard(int size){
    // Clear board content
    ui->board->clearContents();
    ui->board->setColumnCount(size);
    ui->board->setRowCount(size);
    auto *item = new QTableWidgetItem("");
    // Setting rows height
    for (int s = 0; s < size; ++s) {
        ui->board->setRowHeight(s,ui->board->height()/size);
    }
    // Setting columns height
    for (int s = 0; s < size; ++s) {
        ui->board->setColumnWidth(s,ui->board->width()/size);
    }
    // Initializing the table items with an empty value
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            ui->board->setItem(y,x,item);
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    delete newgameform;
}

// To initialize the board with the game specifications
void MainWindow::initializeBoard(){
    // Game mode is SUS
    if(game_mode == "SUS"){
        refreshBoard(3);
        players[0] = new Sus_Player<char>(player1_name.toStdString(),'S');
        board = new Sus_Board<char>();
        if(players_count >= 2)
            players[1] = new Sus_Player<char>(player2_name.toStdString(), 'U');
        else
            players[1] = new Sus_RandomPlayer<char>("Computer", 'U');
    // Game mode is Ultimate
    } else {
        refreshBoard(9);
        players[0] = new Big_Player<char>(player1_name.toStdString(),'X');
        board = new BigBoard<char>();
        if(players_count >= 2)
            players[1] = new Big_Player<char>(player2_name.toStdString(), 'O');
        else
            players[1] = new Big_RandomPlayer<char>("Computer", 'O');
    }
    ui->playagain->setHidden(true);
    ui->winner_label->setText("");
}

// Get data from the form
void MainWindow::getData(){
    this->players_count = newgameform->getPlayersCount();
    this->player1_name = newgameform->getPlayer1Name();
    this->player2_name = newgameform->getPlayer2Name();
    this->game_mode = newgameform->getGameMode();
}

void MainWindow::on_newGame_clicked()
{
    turn = 0;
    if(newgameform->exec() == QDialog::Accepted){
        getData();
        initializeBoard();
    }
}

bool MainWindow::play(int row, int column, char symbol){
    if(board->update_board(column, row, symbol)){
        auto *item = new QTableWidgetItem(QString(symbol));
        item->setTextAlignment(Qt::AlignCenter);
        ui->board->setItem(row,column,item);
        return true;
    } else {
        return false;
    }
}

void MainWindow::on_board_cellClicked(int row, int column)
{
    if(!play(row, column, players[turn]->getsymbol())) return;
    turn = !turn;
    if(!board->game_is_over()){
        if(players_count == 1){
            int x,y;
            do {
                players[turn]->getmove(x,y);
            }while (!play(y, x, players[turn]->getsymbol()));
            turn = !turn;
        }
    }
    if(board->game_is_over()){
        if(board->is_draw()){
            ui->winner_label->setText("<html><head/><body><p><span style=' color:#cccccc;'> Draw</span></p></body></html>");
        } else if(board->is_win()) {
            ui->winner_label->setText("<html><head/><body><p><span style=' color:#2ec27e;'>"+ QString::fromStdString(players[turn]->getname()) +" WINS</span></p></body></html>");
        } else {
            ui->winner_label->setText("<html><head/><body><p><span style=' color:#2ec27e;'>"+ QString::fromStdString(players[!turn]->getname()) +" WINS</span></p></body></html>");
        }
        ui->playagain->setHidden(false);
    }
}


void MainWindow::on_playagain_clicked()
{
    initializeBoard();
    turn = 0;
}

