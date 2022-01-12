#include "Box.h"

Box::Box(QWidget *parent)
    : QPushButton(parent), m_row(0), m_col(0), m_state(Box::Empty) {
    QObject::connect(this, SIGNAL(stateChanged(Box::State,Box::State)),
                     this, SLOT(updateBox(Box::State,Box::State)));
}

Box::~Box(){

}

void Box::setState(Box::State state){
    if(m_state != state){
        Box::State old = m_state;
        m_state = state;
        emit stateChanged(old, state);
    }
}

QPixmap Box::state2pixmap(Box::State state){
    switch(state){
    case Box::Empty:
        return QPixmap(":/empty");
    case Box::Red:
        return QPixmap(":/red");
    case Box::Blue:
        return QPixmap(":/blue");
    case Box::Selectable:
        return QPixmap(":/selectable");
    case Box::Piece:
        return QPixmap(":/piece");
    case Box::Blocked:
        return QPixmap(":/blocked");
    default:
        return QPixmap(":/empty");
    }
}

void Box::updateBox(Box::State old_state, Box::State new_state){
    Q_UNUSED(old_state);

    this->setIcon(Box::state2pixmap(new_state));
}


