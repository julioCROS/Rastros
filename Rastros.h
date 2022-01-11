#ifndef RASTROS_H
#define RASTROS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Rastros; }
QT_END_NAMESPACE

class Rastros : public QMainWindow{
    Q_OBJECT

public:
    Rastros(QWidget *parent = nullptr);
    ~Rastros();

private:
    Ui::Rastros *ui;
};

#endif // RASTROS_H
