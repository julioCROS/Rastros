#include "Rastros.h"
#include "ui_Rastros.h"

#include <QDebug>
#include <QSignalMapper>
#include <QMessageBox>

Rastros::Rastros(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Rastros){
    ui->setupUi(this);

    this->adjustSize();
    this->setFixedSize(this->size());

    QObject_newGame:connect(ui->actionNovo, SIGNAL(triggered(bool)), this, SLOT(reset()));
    QObject_resetGame:connect(ui->actionSair, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    QObject_aboutGame:connect(ui->actionSobre, SIGNAL(triggered(bool)), this, SLOT(showAbout()));

    QSignalMapper* map = new QSignalMapper(this);
       for (int id = 0; id < 64; id++) {
           int r = id / 8;
           int c = id % 8;

           Box* box = this->findChild<Box*>(QString("box%1%2").arg(r).arg(c));
           Q_ASSERT(box != 0);

           m_boxes[id] = box;
           map->setMapping(box, id);
           QObject::connect(box, SIGNAL(clicked(bool)), map, SLOT(map()));
       }
    QObject::connect(map, SIGNAL(mappedInt(int)), this, SLOT(play(int)));

    m_boxes[7]->setState(Box::Blue);
    m_boxes[28]->setState(Box::Piece);
    m_boxes[56]->setState(Box::Red);

}

Rastros::~Rastros(){
    delete ui;
}

void Rastros::play(int id){
    Box* box = m_boxes[id];

    qDebug() << "row: " << box->row();
    qDebug() << "col: " << box->col();
    m_boxes[id]->setState(Box::Piece);
}

void Rastros::reset(){
    for(int id = 0; id < 64; id++){
        Box* box = m_boxes[id];
        box->setState(Box::Empty);
    }

    m_boxes[7]->setState(Box::Blue);
    m_boxes[28]->setState(Box::Piece);
    m_boxes[56]->setState(Box::Red);

}

void Rastros::showAbout(){
    QMessageBox::information(this, tr("Sobre"), tr("Rastros feito por: \n\n - Julio Cesar Rocha: julio.1009@hotmail.com \n\n - Thalles Augusto Soares Verçosa: thalles_augusto2011@hotmail.com"));
}

