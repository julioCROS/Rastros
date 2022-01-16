#include "SlimeTrail.h"
#include "ui_SlimeTrail.h"

#include <QDebug>
#include <QMessageBox>
#include <QActionGroup>
#include <QSignalMapper>

bool firstTurn = true;
int curr_id = 0;

SlimeTrail::Player otherPlayer(SlimeTrail::Player player) {
    return (player == SlimeTrail::RedPlayer ?
                    SlimeTrail::BluePlayer : SlimeTrail::RedPlayer);
}

SlimeTrail::SlimeTrail(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::SlimeTrail),
      m_player(SlimeTrail::RedPlayer){

    ui->setupUi(this);

    QObject::connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(reset()));
    QObject::connect(ui->actionQuit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(showAbout()));
    QObject::connect(this, SIGNAL(gameOver(Player)), this, SLOT(showGameOver(Player)));
    QObject::connect(this, SIGNAL(gameOver(Player)), this, SLOT(reset()));

    QSignalMapper* map = new QSignalMapper(this);
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QString holeName = QString("hole%1%2").arg(row).arg(col);
            Hole* hole = this->findChild<Hole*>(holeName);
            Q_ASSERT(hole != nullptr);
            Q_ASSERT(hole->row() == row && hole->col() == col);

            m_board[row][col] = hole;

            int id = row * 8 + col;
            map->setMapping(hole, id);

            QObject::connect(hole, SIGNAL(clicked(bool)), map, SLOT(map()));
        }
    }

#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    QObject::connect(map, SIGNAL(mapped(int)), this, SLOT(play(int)));
#else
    QObject::connect(map, SIGNAL(mappedInt(int)), this, SLOT(play(int)));
#endif


    // When the turn ends, switch the player.
    QObject::connect(this, SIGNAL(turnEnded()), this, SLOT(switchPlayer()));

    this->reset();

    this->adjustSize();
    this->setFixedSize(this->size());
}

SlimeTrail::~SlimeTrail() {
    delete ui;
}

int SlimeTrail::testHole(int id, int curr_id){
    Hole* hole = NULL;

    int testStates = 0;
    int blackStates = 0;

    int colTests [8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int rowTests [8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    // Teste para saber se a peça branca está cercada
    // por peças pretas
    for(int i = 0; i < 9; i++){
        if((curr_id / 8) + rowTests[i] >= 8  || (curr_id % 8) + colTests[i] >= 8
           || (curr_id / 8) + rowTests[i] < 0 || (curr_id % 8) + colTests[i] < 0){
            continue;
        }else {
            testStates++;
            hole = m_board[(curr_id / 8) + rowTests[i]][(curr_id % 8) + colTests[i]];
            if(hole->state() == Hole::BlackState){
                blackStates++;
            }
        }
    }

    // Se a peça branca estiver cercada de peças pretas
    // então o jogo é finalizado com um EMPATE
    if(blackStates == testStates){
        return -1;
    }

    // Teste para validar se o jogador selecionou ou não
    // uma posição valida para a peça branca
    // 0 -> Posição invalida
    // 1 -> Posição valida
    if(id != curr_id - 9 && id != curr_id - 8 && id != curr_id - 7
              && id != curr_id - 1 && id != curr_id + 1 && id != curr_id + 7
              && id != curr_id + 8 && id != curr_id + 9){
        return 0;
    }

    // Se a peça branca chegar na posição do jogador azul
    // então o jogo é finalizado com VITORIA do jogador vermelho
    if(id == 7){
        return 2;
    }

    // Se a peça branca chegar na posição do jogador vermelho
    // então o jogo é finalizado com VITORIA do jogador azul
    if(id == 56){
        return 3;
    }
    return 1;
}

int SlimeTrail::play(int id) {

    if(firstTurn == true){
        curr_id = 28;
        firstTurn = false;
    }

    qDebug() << "ID: " << id;

    Hole* curr_hole = m_board[curr_id / 8][curr_id % 8];
    Hole* hole = m_board[id / 8][id % 8];

    if(testHole(id, curr_id) == -1){
        qDebug() << "Emitir EMPATE aqui";
    }

    if(testHole(id, curr_id) == 2 ||  testHole(id, curr_id) == 3){
        curr_hole->setState(Hole::BlackState);
        hole->setState(Hole::WhiteState);

        if(testHole(id, curr_id) == 2){
        qDebug() << "Emitir VITORIA AZUL aqui";
        } else if(testHole(id, curr_id) == 3){
            qDebug() << "Emitir VITORIA VERMELHA aqui";
        }
    }

    if(hole->state() != Hole::BlackState && testHole(id, curr_id) == 1){
        curr_hole->setState(Hole::BlackState);
        hole->setState(Hole::WhiteState);
        curr_id = id;
    } else {
        emit turnEnded();
    }
    emit turnEnded();
}

void SlimeTrail::switchPlayer() {
    // Switch the player.
    m_player = otherPlayer(m_player);

    // Finally, update the status bar.
    this->updateStatusBar();
}

void SlimeTrail::reset() {
    // Reset board.
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Hole* hole = m_board[row][col];
            hole->reset();

            // FIXME: Only neighboor holes should be marked.
            hole->setMarked(true);
        }
    }

    // Mark the starting position.
    m_board[3][4]->setState(Hole::WhiteState);
    firstTurn = true;

    // Reset the player.
    m_player = SlimeTrail::RedPlayer;

    // Finally, update the status bar.
    this->updateStatusBar();
}

void SlimeTrail::showAbout() {
    QMessageBox::information(this, tr("Sobre"), tr("SlimeTrail feito por: \n\n - Julio Cesar Rocha: julio.1009@hotmail.com \n\n - Thalles Augusto Soares Verçosa: thalles_augusto2011@hotmail.com"));
}

void SlimeTrail::showGameOver(Player player) {
    switch (player) {
        case SlimeTrail::RedPlayer:
            QMessageBox::information(this, tr("Vencedor"), tr("Parabéns, o jogador vermelho venceu."));
            break;
        case SlimeTrail::BluePlayer:
            QMessageBox::information(this, tr("Vencedor"), tr("Parabéns, o jogador azul venceu."));
            break;
        default:
            Q_UNREACHABLE();
    }
}

void SlimeTrail::updateStatusBar() {
    QString player(m_player == SlimeTrail::RedPlayer ? "Vermelho" : "Azul");
    ui->statusbar->showMessage(tr("Vez do Jogador %2").arg(player));
}
