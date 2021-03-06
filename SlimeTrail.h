#ifndef SLIMETRAIL_H
#define SLIMETRAIL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class SlimeTrail;
}
QT_END_NAMESPACE

class Hole;

class SlimeTrail : public QMainWindow {
    Q_OBJECT

public:
    enum Player {
        RedPlayer,
        BluePlayer,
        DrawPlayer
    };
    Q_ENUM(Player)

    SlimeTrail(QWidget *parent = nullptr);
    virtual ~SlimeTrail();

signals:
    void turnEnded();
    void gameOver(Player player);

private:
    Ui::SlimeTrail *ui;
    Player m_player;
    Hole* m_board[8][8];

private slots:
    int play(int id);
    int testHole(int id, int curr_id);
    void switchPlayer();
    void reset();

    void showAbout();
    void showGameOver(Player player);
    void updateStatusBar();

};

#endif // SLIMETRAIL_H
