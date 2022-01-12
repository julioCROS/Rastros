#ifndef BOX_H
#define BOX_H

#include <QPushButton>

class Box : public QPushButton{
    Q_OBJECT
    Q_PROPERTY(int row READ row WRITE setRow);
    Q_PROPERTY(int col READ col WRITE setCol);
    Q_PROPERTY(Box::State state READ state WRITE setState NOTIFY stateChanged)

public:
    enum State{
        Empty,
        Red,
        Blue,
        Selectable,
        Piece,
        Blocked
    };
    Q_ENUM(State)

    explicit Box(QWidget *parent = nullptr);
    virtual ~Box();

    int row() const { return m_row; }
    void setRow(int row) { m_row = row; }

    int col() const { return m_col; }
    void setCol(int col) { m_col = col; }

    Box::State state() const { return m_state; }
    void setState(Box::State state);

signals:
    void stateChanged(Box::State old_state, Box::State new_state);
private:
    int m_row;
    int m_col;
    Box::State m_state;

    static QPixmap state2pixmap(Box::State state);

private slots:
    void updateBox(Box::State old_state, Box::State new_state);
};

#endif // BOX_H
