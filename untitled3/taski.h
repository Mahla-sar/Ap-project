#ifndef TASKI_H
#define TASKI_H

#include <QMainWindow>

namespace Ui {
class Taski;
}

class Taski : public QMainWindow
{
    Q_OBJECT

public:
    explicit Taski(QWidget *parent = nullptr);
    ~Taski();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Taski *ui;
};

#endif // TASKI_H
