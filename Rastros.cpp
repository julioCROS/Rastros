#include "Rastros.h"
#include "ui_Rastros.h"

#include <QDebug>

Rastros::Rastros(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Rastros){
    ui->setupUi(this);

    this->adjustSize();
    this->setFixedSize(this->size());


    qDebug() << "row: " << ui->box00->row();
    qDebug() << "col: " << ui->box00->col();
}

Rastros::~Rastros(){
    delete ui;
}

