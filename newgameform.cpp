#include "newgameform.h"
#include "ui_newgameform.h"

NewGameForm::NewGameForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewGameForm)
{
    ui->setupUi(this);
    player1_name = "";
    player2_name = "";
    game_mode = "";
    players_count = 1;
}

NewGameForm::~NewGameForm()
{
    delete ui;
}


// Accepted form taking the data to the object
void NewGameForm::on_buttonBox_accepted()
{
    this->player1_name = ui->player1_name->text();
    this->player2_name = ui->player2_name->text();
    this->players_count = ui->players_count->currentIndex() + 1;
    this->game_mode = ui->game_mode->currentText();
}



// If he choosed to switch the number of players
void NewGameForm::on_players_count_currentIndexChanged(int index)
{
    if(index == 1){
        ui->label_2->setEnabled(true);
        ui->player2_name->setEnabled(true);
    }else {
        ui->label_2->setEnabled(false);
        ui->player2_name->setEnabled(false);
    }
}
// some getters
QString NewGameForm::getPlayer1Name(){
    return this->player1_name;
}
QString NewGameForm::getPlayer2Name(){
    return this->player2_name;
}

QString NewGameForm::getGameMode(){
    return this->game_mode;
}

int NewGameForm::getPlayersCount(){
    return this->players_count;
}

// when he cancel creating the game
void NewGameForm::on_buttonBox_rejected()
{
    delete ui;
}

