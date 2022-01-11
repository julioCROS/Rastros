#ifndef BOX_H
#define BOX_H

#include <QPushButton>

class Box : public QPushButton{
    Q_OBJECT
    Q_PROPERTY(int row READ row WRITE setRow);
    Q_PROPERTY(int col READ col WRITE setCol);

public:
    explicit Box(QWidget *parent = nullptr);
    virtual ~Box();

    int row() const { return m_row; }
    void setRow(int row) { m_row = row; }

    int col() const { return m_col; }
    void setCol(int col) { m_col = col; }


signals:

private:
    int m_row;
    int m_col;

};

#endif // BOX_H
