#ifndef NEWGAMEFORM_H
#define NEWGAMEFORM_H

#include <QDialog>

namespace Ui {
class NewGameForm;
}

class NewGameForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameForm(QWidget *parent = nullptr);
    ~NewGameForm();
    int getPlayersCount();
    QString getGameMode();
    QString getPlayer1Name();
    QString getPlayer2Name();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_players_count_currentIndexChanged(int index);

private:
    Ui::NewGameForm *ui;
    int players_count;
    QString game_mode;
    QString player1_name;
    QString player2_name;
};

#endif // NEWGAMEFORM_H
