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
    ui->playagain->setHidden(true); // Hide the play again button
    ui->winner_label->setText(""); // Empty the winner label
}

// Get data from the dialog
void MainWindow::getData(){
    this->players_count = newgameform->getPlayersCount();
    this->player1_name = newgameform->getPlayer1Name();
    this->player2_name = newgameform->getPlayer2Name();
    this->game_mode = newgameform->getGameMode();
}

// When creating a new game
void MainWindow::on_newGame_clicked()
{
    turn = 0; // Set the turn for player 1
    if(newgameform->exec() == QDialog::Accepted){
        getData(); // get the game specifications from the user
        initializeBoard(); // initialize a clear suitable board to his specifications
    }
}

// Set a move position using a symbol
bool MainWindow::play(int row, int column, char symbol){
    if(board->update_board(column, row, symbol)){ // valid play
        auto *item = new QTableWidgetItem(QString(symbol));
        item->setTextAlignment(Qt::AlignCenter); // centering the symbol
        ui->board->setItem(row,column,item);
        return true;
    } else { // invalid play
        return false;
    }
}

// When playing a turn
void MainWindow::on_board_cellClicked(int row, int column)
{
    // Check if the play is valid and if so he play it
    if(!play(row, column, players[turn]->getsymbol())) return;
    turn = !turn; // switch the turn for the other player
    if(!board->game_is_over() && players_count == 1){ // if the game didn't end the the second player was the computer
        int x,y;
        do {
            players[turn]->getmove(x,y); // randomizing a move
        }while (!play(y, x, players[turn]->getsymbol())); // is it's not valid it try again
        turn = !turn; // switching the turn again for the human playing
    }
    if(board->game_is_over()){ // if game is over show out the winner
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


// When play again button is pressed
void MainWindow::on_playagain_clicked()
{
    initializeBoard(); // initialize a clear board depending on the game mode
    turn = 0; // The turn is for player 1
}

