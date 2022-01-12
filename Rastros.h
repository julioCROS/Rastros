#ifndef RASTROS_H
#define RASTROS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Rastros; }
QT_END_NAMESPACE

class Box;
class Rastros : public QMainWindow{
    Q_OBJECT

public:
    Rastros(QWidget *parent = nullptr);
    ~Rastros();

private:
    Ui::Rastros *ui;
    Box* m_boxes[64];

private slots:
    void play(int id);
    void reset();
    void showAbout();

};

#endif // RASTROS_H
